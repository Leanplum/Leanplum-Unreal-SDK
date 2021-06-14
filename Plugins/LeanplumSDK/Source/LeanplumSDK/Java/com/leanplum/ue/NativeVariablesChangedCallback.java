package com.leanplum.ue;

import com.leanplum.callbacks.VariablesChangedCallback;

public class NativeVariablesChangedCallback extends VariablesChangedCallback {

    private long nativeHandle = 0;

    @Override
    public void variablesChanged() {
        on_variables_changed();
    }

    private native void on_variables_changed();
}