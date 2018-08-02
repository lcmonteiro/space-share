/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package NetShare;

import com.share.cwrapper.netshare.NetShare;
import java.io.IOException;
import java.net.Socket;

/**
 *
 * @author monteiro
 */
public class Test {

        /**
         * @param args the command line arguments
         */
        public static void main(String[] args) throws InterruptedException {

                System.setProperty("java.library.path", "/home/monteiro/workspace/m2bee/C++/ShareSpace/Applications/NetShare/Java/NetShare/libs/");
                System.out.println(System.getProperty("java.library.path"));
                NetShare.SetReference(3);
                
                NetShare net = new NetShare("a", "");
                Socket socket = net.Connect(10);
                
                while (true) {
                        System.out.println(net.Status());
                        Thread.sleep(1000);
                }
        }

}
