/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.share.cwrapper.buffershare;
/**
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Luis Monteiro
 */
public class BufferShare {
        /**
         *
         */
        protected BufferShare() {
                _id = ++__counter;
        }
        /**
         * instance id
         */
        protected int _id = 0;
        /**
         * uid
         */
        private static int __counter;
        /**
         * native interface functions
         */
        protected static final int ENCODE = 0;
        protected static final int DECODE = 1;
        /**
         */
        protected native final boolean Open(int coder, int id);

        protected native final int Encode(byte[] buffer, int frameSize, int id);

        protected native final byte[] GetFrame(int id);

        protected native final boolean SetFrame(byte[] buffer, int id);

        protected native final byte[] Decode(int id);

        protected native final boolean Close(int coder, int id);

        /**
         * native interface functions
         */
        static {
                if (!LoadLibrary()) {
                        throw new UnsatisfiedLinkError("Unable to locate libShareNative");
                }
        }
        /**
         * load native library
         */
        static boolean LoadLibrary() {
                if (LoadLibrary(System.getProperty("os.arch"))) {
                        return true;
                }
                for (String arch : new String[]{"arm", "arm64", "mips", "mips64", "x86", "x86_64"}) {
                        if (LoadLibrary(arch)) {
                                return true;
                        }
                }
                return false;
        }
        static boolean LoadLibrary(String arch) {
                try {
                        File temp = File.createTempFile("libShareNative", "so");
                        temp.deleteOnExit();
                        // Open and check input stream
                        InputStream is = BufferShare.class.getResourceAsStream("/BufferShare/" + arch + "/libBufferShareNative.so");
                        if (is == null) {
                                throw new FileNotFoundException("File libShareNative.so was not found inside JAR.");
                        }
                        // Open output stream and copy data between source file in JAR and the temporary file
                        try (OutputStream os = new FileOutputStream(temp)) {
                                // Prepare buffer for data copying
                                byte[] buffer = new byte[1024];
                                int readBytes;
                                while ((readBytes = is.read(buffer)) != -1) {
                                        os.write(buffer, 0, readBytes);
                                }
                        } finally {
                                is.close();
                        }
                        // Finally, load the library
                        System.load(temp.getAbsolutePath());
                } catch (UnsatisfiedLinkError | IOException e) {
                        return false;
                }
                return true;
        }
}
