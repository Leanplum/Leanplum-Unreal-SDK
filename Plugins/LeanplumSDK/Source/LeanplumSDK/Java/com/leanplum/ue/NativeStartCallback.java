package com.leanplum.ue;

import com.leanplum.callbacks.StartCallback;

public class NativeStartCallback extends StartCallback {

    private long nativeHandle = 0;

    @Override
    public void onResponse(boolean success) {
        on_start(success);
    }

    private native void on_start(boolean success);
}
