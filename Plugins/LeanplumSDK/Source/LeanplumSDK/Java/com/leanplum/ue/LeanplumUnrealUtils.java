package com.leanplum.ue;

import com.leanplum.Leanplum;
import com.leanplum.SecuredVars;
import com.leanplum.internal.VarCache;
import com.leanplum.internal.JsonConverter;

import java.util.HashMap;

public class LeanplumUnrealUtils {
    
    public static String getVars() {
        return JsonConverter.toJson(VarCache.getDiffs());
    }

    public static HashMap<String, String> getSecuredVars() {
        SecuredVars securedVars = Leanplum.securedVars();
        
        if (securedVars != null) {
            HashMap<String, String> map = new HashMap();
            map.put("json", securedVars.getJson());
            map.put("signature", securedVars.getSignature());
            
            return map;
        }
        return null;
    }
}
