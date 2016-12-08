package com.kevin.uselibjpegturbo;

import android.graphics.Bitmap;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;

import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {

    private ImageView imageView;

    static {
        System.loadLibrary("uselib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        imageView = (ImageView) findViewById(R.id.iv_girl);

        File sdcard = Environment.getExternalStorageDirectory();

        //Get the text file
        File file = new File(sdcard,"/Download/20161-8.jpg");
        int jpegBitsLen = (int) file.length();
        byte[] jpegBits = new byte[jpegBitsLen];
        DataInputStream dis;
        try {
            dis = new DataInputStream(new FileInputStream(file));
            dis.readFully(jpegBits);
            dis.close();
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }


        long jpegDec = tjInitDecompress();

        int wh = tjDecompressHeader2(jpegDec, jpegBits, jpegBitsLen);
        int width = wh>>16;
        int height = wh&0x7fff;

        int[] buffer = new int[width*height];
        tjDecompress2(jpegDec, jpegBits, jpegBitsLen, buffer, width, 0/*pitch*/, height, 8 /*TJPF_RGBX*/, 0);

        tjDestroy(jpegDec);

        Bitmap bmp = Bitmap.createBitmap(buffer, width, height, Bitmap.Config.ARGB_8888);

        imageView.setImageBitmap(bmp);
    }


    public native long tjInitDecompress();
    public native int tjDecompressHeader2(long handle, byte[] jpegBits, int jpegBitsLen);
    public native void tjDecompress2(long handle, byte[] jpegBits,
                                     int jpegBitsLen, int[] outbuffer, int width, int pitch, int height,
                                     int pixelFormat, int flags);
    public native void tjDestroy(long handle);

}
