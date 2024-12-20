class C {
    static {
        System.loadLibrary("HelloWorld");
    }

    public static void main(String[] args) {
        new C().print();
    }

    private native void print();
    private native void g();
}