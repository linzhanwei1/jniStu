class ConstructorCall {
	private native String MyNewString();

	public static void main(String[] args) {
		ConstructorCall c = new ConstructorCall();
        System.out.println("In Java: " + c.MyNewString());
	}

	static { System.loadLibrary("ConstructorCall"); }
}
