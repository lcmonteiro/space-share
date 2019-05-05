/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package com.share.buffershare;
/**
 *
 * @author Luis Monteiro
 */
public class IBufferShare extends BufferShare {
	/**
	 * create decoder
	 */
	public IBufferShare() {
		super();
		/**
		 * open encoder
		 */
		if (!Open(DECODE, _id)) {
			throw new UnsupportedOperationException();
		}
	}
	/**
	 * frame is decoded
	 */
	public boolean Full() {
		return __done;
	}
	/**
	 * set coded frame
	 */
	public void Set(byte[] frame) {
		__done = SetFrame(frame, _id);
	}
	/**
	 * get buffer
	 */
	public byte[] Get() {
		return Decode(_id);
	}
	/**
	 * release decoder
	 */
	@Override
	protected void finalize() throws Throwable {
		Close(DECODE, _id);
		super.finalize();
	}
	/**
	 * context
	 */
	private boolean __done = false;
}
