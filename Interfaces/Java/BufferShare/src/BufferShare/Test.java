/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package BufferShare;
/**
 * 
 */
import com.share.cwrapper.buffershare.IBufferShare;
import com.share.cwrapper.buffershare.OBufferShare;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
/**
 * @author Luis Monteiro
 */
public class Test {
	/**
	 * test
	 */
	public static void main(String[] args) {
		try {
			byte[] frame = null;
			byte[] data = new byte[10];
                        List<byte[]> link = new ArrayList<>();
                        /**
			 * create data
			 */
                        new Random().nextBytes(data);
			System.out.println("data in=" + Arrays.toString(data));
                        /**
			 * out buffer
                         * 
			 */
			OBufferShare out = new OBufferShare(30, 1);
			/**
			 */
			out.Set(data);
			for(frame = out.Get(); !out.Empty(); frame = out.Get()){
				/**
				 * write frame to link
				 */
                                link.add(frame);
				System.out.println("frame=" + Arrays.toString(frame));
			}
			/**
			 * in buffer
			 */
			IBufferShare in = new IBufferShare();
			/**
			 */
			for(; !in.Full(); in.Set(frame)){
				/**
				 * read from link
				 */
                                frame = link.remove(0);
			}
			/**
			 */
			data = in.Get();
			/**
			 * write data
			 */
			System.out.println("data out=" + Arrays.toString(data));
			System.out.flush();
			/**
			 */
		} catch (Exception e) {
			System.out.println("exception" + e.getMessage());
		}
	}

}
