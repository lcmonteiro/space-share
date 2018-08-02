/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.share.cwrapper.netshare;

import com.sun.org.apache.xml.internal.security.Init;
import java.net.Socket;
import java.util.HashSet;
import java.util.Set;

/**
 *
 * @author monteiro
 */
public class NetShare {

        /**
         * instance id
         */
        private int __id = 0;

        /**
         * constructor
         */
        public NetShare(String location, String password) {
                synchronized (__instances) {
                        /**
                         * allocate id
                         */
                        while (!__instances.add(__id)) {
                                ++__id;
                        }
                        /**
                         * open
                         */
                        if (!Open(location, password, __id, __reference)) {
                                throw new RuntimeException("open");
                        }
                }
        }

        /**
         * connect socket
         */
        public Socket Connect(int n) throws InterruptedException {
                for (int i = 0; i < n; ++i) {
                        Thread.sleep(1000);
                        try {
                                return new Socket("localhost", (__reference + __id * 100));
                        } catch (Exception e) {
                        }
                }
                throw new InterruptedException();
        }

        /**
         * Status
         */
        public float Status() {
                return Good(__id);
        }

        /**
         * Destroy
         */
        public void Destroy() {
                synchronized (__instances) {
                        /**
                         * free id
                         */
                        __instances.remove(__id);
                        /**
                         * close network
                         */
                        Close(__id);
                }
        }

        /**
         * Release decoder
         */
        @Override
        protected void finalize() throws Throwable {
                Destroy();
                super.finalize();
        }
        /**
         * ------------------------------------------------------------------------------------------------------------
         * static
         * ------------------------------------------------------------------------------------------------------------
         */
        final private static Set<Integer> __instances = new HashSet<Integer>();
        /**
         * reference
         */
        private static int __reference = 10000;

        /**
         * move reference
         */
        public static void SetReference(int n) {
                __reference += (n * 100);
        }

        /*-------------------------------------------------------------------------------------------------------------*
         * native interface functions
         *-------------------------------------------------------------------------------------------------------------*/
        /**
         */
        protected static native final boolean Init();
        
        protected static native final boolean Open(String location, String password, int id, int ref);

        protected static native final float Good(int id);

        protected static native final boolean Close(int id);
        /**
         * load library
         */
        static {
                try {
//                        System.loadLibrary("netshare");
                        System.load("/home/monteiro/workspace/m2bee/C++/ShareSpace/Applications/NetShare/Java/NetShare/libs/amd64/libnetshare.so");
                        //
                        Init();
                } catch (UnsatisfiedLinkError e) {
                        System.err.println(e.toString());
                }
        }

}
