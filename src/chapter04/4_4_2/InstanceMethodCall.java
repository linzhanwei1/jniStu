class InstanceMethodCall {
	private static native void initIDS();
	private native void nativeMethod();
	private void callback() {
		System.out.println("In Java");
	}
	public static void main(String[] args) {
		InstanceMethodCall c = new InstanceMethodCall();
		c.nativeMethod();
	}

	static {
		System.loadLibrary("InstanceMethodCall");
		initIDS();	// Caching in the Defining class's Initializer
	}
}
