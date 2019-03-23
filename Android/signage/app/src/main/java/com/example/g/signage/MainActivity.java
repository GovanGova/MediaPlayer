package com.example.g.signage;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.view.SurfaceView;
import android.view.View;
import android.widget.TextView;
import android.view.SurfaceHolder;
import android.view.Surface;
import android.view.View.OnClickListener;
import android.widget.Toast;
import android.content.Intent;
import android.net.Uri;
import  android.provider.MediaStore;
import  android.database.Cursor;


public class MainActivity extends Activity implements SurfaceHolder.Callback {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    private static final int SELECT_PICTURE = 1;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //allow only landscape
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        setContentView(R.layout.activity_main);

        //Get surface view
        SurfaceView surfaceView= (SurfaceView)findViewById(R.id.surfaceView);
        surfaceView.getHolder().addCallback(this);
        surfaceView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN| View.SYSTEM_UI_FLAG_HIDE_NAVIGATION|
                                            View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);

        // add onclick event
        surfaceView.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {

//                SurfaceView surfaceView= (SurfaceView)findViewById(R.id.surfaceView);
//
//                surfaceView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION);
            }
        });


        // Example of a call to a native method

    }

    @Override
    protected void onStart(){
        super.onStart();
        //SurfaceView surfaceView= (SurfaceView)findViewById(R.id.surfaceView);
        //surfaceView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN| View.SYSTEM_UI_FLAG_HIDE_NAVIGATION|
                //View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
//        Toast text=Toast.makeText(MainActivity.this,
//                "Started",
//                Toast.LENGTH_SHORT);
//        text.show();
        nativeOnStart();
        System.out.print("started activity \n");
    }

    @Override
    protected void onRestart(){
        super.onRestart();
//        Toast text=Toast.makeText(MainActivity.this,
//                "ReStarted",
//                Toast.LENGTH_SHORT);
//        text.show();
        System.out.print("restarted activity \n");
    }
    @Override
    protected void onResume(){
        super.onResume();
//        Toast text=Toast.makeText(MainActivity.this,
//                "resume",
//                Toast.LENGTH_SHORT);
//        text.show();
        //nativeOnResume();
        System.out.print("resumed activity \n");

    }

    @Override
    protected void onPause(){
        super.onPause();
//        Toast text=Toast.makeText(MainActivity.this,
//                "paused",
//                Toast.LENGTH_SHORT);
//        text.show();
       // nativeOnPause();
        System.out.print("paused activity \n");
    }

    @Override
    protected void onStop(){
        super.onStop();
//        Toast text=Toast.makeText(MainActivity.this,
//                "stopped",
//                Toast.LENGTH_SHORT);
//        text.show();
        nativeOnStop();
        System.out.print("stopped activity \n");
    }

    @Override
    protected void onDestroy(){
        super.onDestroy();
//        Toast text=Toast.makeText(MainActivity.this,
//                "destroy",
//                Toast.LENGTH_SHORT);
//        text.sh
        System.out.print("destroyed activity \n");
    }

    public void surfaceCreated(SurfaceHolder holder){
        System.out.print("surfaceCreated \n");
//        Toast text=Toast.makeText(MainActivity.this,
//                "surfacecreated",
//                Toast.LENGTH_SHORT);
//        text.show();

    }
    public void surfaceDestroyed(SurfaceHolder holder){
        System.out.print("surfaceDestroyed \n");
//        Toast text=Toast.makeText(MainActivity.this,
//                "surfaceDestroy",
//                Toast.LENGTH_SHORT);
//        text.show();
        System.out.print("Surface destroyed \n");
        nativeOnSurfaceDestroyed();
    }

    public void surfaceChanged (SurfaceHolder holder,
                         int format,
                         int width,
                         int height){

        System.out.print("Surface change \n");
       setSurface(holder.getSurface(), format, width, height);

    }

    public void onClickShapeBtn(View v)
    {
        createShape();
    }
    public void hideLayout(View v){
        Intent intent = new Intent();
        intent.setType("image/*");
        intent.setAction(Intent.ACTION_GET_CONTENT);
        startActivityForResult(Intent.createChooser(intent, "Select Picture"), SELECT_PICTURE);

    }

   @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        if (requestCode == SELECT_PICTURE) {
            Uri selectedImageUri = data.getData();
            String selectedImagePath = selectedImageUri.getPath();
            String realPath = ImageFilePath.getPath(this, data.getData());
            Toast text=Toast.makeText(this,
                    realPath,
                    Toast.LENGTH_LONG);
            text.show();

            createTexture(realPath);
        }
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public static native void setSurface(Surface surface, int format, int w, int h);
    public static native void nativeOnStart();
    public static native void nativeOnResume();
    public static native void nativeOnPause();
    public static native void nativeOnDesroy();
    public static native void nativeOnStop();
    public static native void nativeOnSurfaceDestroyed();
    public static native void createShape();
    public static native void createTexture(String filename);
}
