class HelloWorld {
    static {
        System.loadLibrary("HelloWorld");
    }

    public static void main(String[] args) {
        new HelloWorld().print();
    }

    private native void print();
}