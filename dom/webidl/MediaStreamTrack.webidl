/* -*- Mode: IDL; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * The origin of this IDL file is
 * http://dev.w3.org/2011/webrtc/editor/getusermedia.html
 *
 * Copyright © 2012 W3C® (MIT, ERCIM, Keio), All Rights Reserved. W3C
 * liability, trademark and document use rules apply.
 */

// Important! Do not ever add members that might need tracing (e.g. object)
// to MediaTrackConstraintSet or any dictionary marked XxxInternal here

enum VideoFacingModeEnum {
    "user",
    "environment",
    "left",
    "right"
};

dictionary MediaTrackConstraintSet {
    VideoFacingModeEnum facingMode;
};

// MediaTrackConstraint = single-property-subset of MediaTrackConstraintSet
// Implemented as full set. Test Object.keys(pair).length == 1

// typedef MediaTrackConstraintSet MediaTrackConstraint; // TODO: Bug 913053

dictionary MediaTrackConstraints {
    object mandatory; // so we can see unknown + unsupported constraints
    sequence<MediaTrackConstraintSet> _optional; // a.k.a. MediaTrackConstraint
};

// Internal dictionary holds result of processing raw MediaTrackConstraints above

dictionary MediaTrackConstraintsInternal {
    MediaTrackConstraintSet mandatory; // holds only supported constraints
    sequence<MediaTrackConstraintSet> _optional; // a.k.a. MediaTrackConstraint
};

interface MediaStreamTrack {
    readonly    attribute DOMString             kind;
    readonly    attribute DOMString             id;
    readonly    attribute DOMString             label;
                attribute boolean               enabled;
//    readonly    attribute MediaStreamTrackState readyState;
//    readonly    attribute SourceTypeEnum        sourceType;
//    readonly    attribute DOMString             sourceId;
//                attribute EventHandler          onstarted;
//                attribute EventHandler          onmute;
//                attribute EventHandler          onunmute;
//                attribute EventHandler          onended;
//    any                    getConstraint (DOMString constraintName, optional boolean mandatory = false);
//    void                   setConstraint (DOMString constraintName, any constraintValue, optional boolean mandatory = false);
//    MediaTrackConstraints? constraints ();
//    void                   applyConstraints (MediaTrackConstraints constraints);
//    void                   prependConstraint (DOMString constraintName, any constraintValue);
//    void                   appendConstraint (DOMString constraintName, any constraintValue);
//                attribute EventHandler          onoverconstrained;
//    void                   stop ();
};
