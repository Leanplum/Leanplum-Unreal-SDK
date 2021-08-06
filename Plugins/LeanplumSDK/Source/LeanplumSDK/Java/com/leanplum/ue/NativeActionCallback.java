package com.leanplum.ue;

import com.leanplum.ActionContext;
import com.leanplum.callbacks.ActionCallback;

public class NativeActionCallback extends ActionCallback {

    private long nativeHandle = 0;

    @Override
    public boolean onResponse(ActionContext context) {
        on_action_callback(context);
        return true;
    }

    private native void on_action_callback(ActionContext context);
}
