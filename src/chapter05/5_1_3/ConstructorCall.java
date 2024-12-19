class ConstructorCall {
	private native String MyNewString();

	public static void main(String[] args) {
		ConstructorCall c = new ConstructorCall();
        System.out.println("In Java: " + c.MyNewString());
		System.out.println("In Java: " + c.MyNewString());	// A fatal error has been detected by the Java Runtime Environment:
	}

	static { System.loadLibrary("ConstructorCall"); }
}
