/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.share.cwrapper.buffershare;
/**
 *
 * @author Luis Monteiro
 */
public class OBufferShare extends BufferShare {
	/**
	 * create encoder
	 */
	public OBufferShare(int frameSize, int redundancy) {
		super();
		/**
		 * open encoder
		 */
		if (!Open(ENCODE, _id)) {
			throw new UnsupportedOperationException();
		}
		/**
		 * settings
		 */
		__size = redundancy;
		/**
		 */
		__frameSize = frameSize;
	}
	/**
	 * all coded
	 * @return 
	 */
	public boolean Empty() {
		return __size == 0;
	}
	/**
	 * set buffer
	 */
	public void Set(byte[] buffer) {
		__size += Encode(buffer, __frameSize, _id);
	}
	/**
	 * get coded frame
	 */
	public byte[] Get() {
		--__size;
		return GetFrame(_id);
	}
	/**
	 * release encoder
	 */
	@Override
	protected void finalize() throws Throwable {
		Close(ENCODE, _id);
		super.finalize();
	}
	/**
	 * context
	 */
	private int __frameSize;
	private int __size;

}
