class RegisteringNativeMethod {
    static {
        System.loadLibrary("RegisteringNativeMethod");
    }

    public static void main(String[] args) {
        RegisteringNativeMethod obj = new RegisteringNativeMethod();
        obj.firstFunction();
        int num = obj.SecondFunction();
        System.out.println("num: " + num);
    }

    private native void firstFunction();
    private native int SecondFunction();
}