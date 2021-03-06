/* -*- Mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; tab-width: 40 -*- */
/* vim: set ts=2 et sw=2 tw=40: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef DOM_CAMERA_DOMCAMERAMANAGER_H
#define DOM_CAMERA_DOMCAMERAMANAGER_H

#include "mozilla/dom/BindingDeclarations.h"
#include "nsCOMPtr.h"
#include "nsAutoPtr.h"
#include "nsIObserver.h"
#include "nsHashKeys.h"
#include "nsWrapperCache.h"
#include "nsWeakReference.h"
#include "nsClassHashtable.h"
#include "nsCycleCollectionParticipant.h"
#include "mozilla/Attributes.h"

class nsPIDOMWindow;

namespace mozilla {
  class ErrorResult;
  class nsDOMCameraControl;
  namespace dom {
    class CameraConfiguration;
    class GetCameraCallback;
    class CameraErrorCallback;
  }
}

typedef nsTArray<nsRefPtr<mozilla::nsDOMCameraControl> > CameraControls;
typedef nsClassHashtable<nsUint64HashKey, CameraControls> WindowTable;
typedef mozilla::dom::Optional<mozilla::dom::OwningNonNull<mozilla::dom::CameraErrorCallback>>
          OptionalNonNullCameraErrorCallback;

class nsDOMCameraManager MOZ_FINAL
  : public nsIObserver
  , public nsSupportsWeakReference
  , public nsWrapperCache
{
public:
  NS_DECL_CYCLE_COLLECTING_ISUPPORTS
  NS_DECL_CYCLE_COLLECTION_SCRIPT_HOLDER_CLASS_AMBIGUOUS(nsDOMCameraManager,
                                                         nsIObserver)
  NS_DECL_NSIOBSERVER

  static bool CheckPermission(nsPIDOMWindow* aWindow);
  static already_AddRefed<nsDOMCameraManager>
    CreateInstance(nsPIDOMWindow* aWindow);
  static bool IsWindowStillActive(uint64_t aWindowId);

  void Register(mozilla::nsDOMCameraControl* aDOMCameraControl);
  void OnNavigation(uint64_t aWindowId);

  void PermissionAllowed(uint32_t aCameraId,
                         const mozilla::dom::CameraConfiguration& aOptions,
                         mozilla::dom::GetCameraCallback* aOnSuccess,
                         mozilla::dom::CameraErrorCallback* aOnError);

  void PermissionCancelled(uint32_t aCameraId,
                           const mozilla::dom::CameraConfiguration& aOptions,
                           mozilla::dom::GetCameraCallback* aOnSuccess,
                           mozilla::dom::CameraErrorCallback* aOnError);

  // WebIDL
  void GetCamera(const nsAString& aCamera,
                 const mozilla::dom::CameraConfiguration& aOptions,
                 mozilla::dom::GetCameraCallback& aOnSuccess,
                 const OptionalNonNullCameraErrorCallback& aOnError,
                 mozilla::ErrorResult& aRv);
  void GetListOfCameras(nsTArray<nsString>& aList, mozilla::ErrorResult& aRv);

  nsPIDOMWindow* GetParentObject() const { return mWindow; }
  virtual JSObject* WrapObject(JSContext* aCx)
    MOZ_OVERRIDE;

protected:
  void XpComShutdown();
  void Shutdown(uint64_t aWindowId);
  ~nsDOMCameraManager();

private:
  nsDOMCameraManager() MOZ_DELETE;
  nsDOMCameraManager(nsPIDOMWindow* aWindow);
  nsDOMCameraManager(const nsDOMCameraManager&) MOZ_DELETE;
  nsDOMCameraManager& operator=(const nsDOMCameraManager&) MOZ_DELETE;

protected:
  uint64_t mWindowId;
  uint32_t mPermission;
  nsCOMPtr<nsPIDOMWindow> mWindow;
  /**
   * 'sActiveWindows' is only ever accessed while in the Main Thread,
   * so it is not otherwise protected.
   */
  static ::WindowTable* sActiveWindows;
};

#endif // DOM_CAMERA_DOMCAMERAMANAGER_H
