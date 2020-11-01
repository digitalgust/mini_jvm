
![](/screenshot/mini_jvm_64.png)  
[![Build Status](https://travis-ci.org/digitalgust/miniJVM.svg?branch=master)](https://travis-ci.org/digitalgust/miniJVM)
# miniJVM

  Develop iOS Android app in java, Cross platform java virtual machine , the minimal jvm . 
  
## Features:  

  * Jvm Build pass: iOS / Android / mingww64 32|64bit / cygwin / MSVC 32|64bit / MacOS /  Linux  .   
  * No dependence Library .  
  * Minimal memory footprint .  
  * Minimal binary, embedded jvm.  
  * Minimal bootstrap classlib .   
  * Support embedded java source compiler(janino compiler) .  
  * Jit supported .    
  *  Low latency  java garbage collection .   
  * Java remote debug supported, JDWP Spec .  
  
## iOS/Android Platform Extended Features:  
  * OpenGL ES 2.0 / 3.0 .  
  * Swing like gui lib, XML gui html like layout.    
  * Audio Playback and Capture .  
  * Take photo from Camera or Album .  
  * Save and Load file from mobile storage .   
  * Api compatible with miniJVM desktop platform,  app can running on desktop platform .  
  * Compile minijvm java source code to C boost performance.  Source on [java2c](https://github.com/digitalgust/java2c) .  

## Demo

  <div align=center><img width="224" height="398" src="/screenshot/demo.gif"/><img width="224" height="398" src="/screenshot/g3d.gif"/></div>

  * Instant Message app  Demo , source on :https://github.com/digitalgust/BiBiX     
  * BiBiX binary can be download from : http://bb.egls.cn:8080/down/BiBiX.jar     
  * 3D game app Demo, source on :https://github.com/digitalgust/g3d     
  * G3D binary can be download from : http://bb.egls.cn:8080/down/g3d.jar     
  * Mobile platform : First build and install AppManager for iOS /mobile/iosapp , Or build and install for Android /mobile/androidapp ,then download demo in AppManager and run these app.     
  * Desktop computer: /binary/win_64  , /binary/macos , /binary/win32 , /binary/centos_x64   run test.sh 


## Architecture:  

  <div align=center><img width="540" height="350" src="https://raw.githubusercontent.com/digitalgust/miniJVM/master/screenshot/arch.png"/></div>


## Changelog:
   2020.10.  Refactor source and remove binary in repository.   
   2020.10.  Https supported.   
   2020.03.  Add xml layout for gui system, add 3D game demo for minijvm, fix jdwp debug for jetbrain idea.               
   2019.12.  Bind cross platform awtk ui system , see [awtk-minijvm](https://github.com/digitalgust/miniJVM/tree/master/desktop/awtk_gui)   
   2019.12.  Jit enabled, it based on sljit project   
   2019.10.  Jit is developing   
   2018.12.  Optimize performance     
   2017.09.  miniJVM start   


## How to develop iOS/Android app in java:   
   Write java code once , running on all of iOS / Android / MacOSX / Win / Linux platforms.   
   * Develop app by Eclipse, Netbeans or Intelli Idea , or any IDE .   
   * Build maven projects /minijvm/java and /mobile/java/glfm_gui, it world copy generated jar to  **/mobile/assets/resfiles/minijvm_rt.jar** and **/mobile/assets/resfiles/glfm_gui.jar**     
   * Open maven project ExApp in IDE ,or create new project same as ExApp   
   * Write your code like example **/mobile/java/ExApp/src/main/java/test/MyApp.java**    
   * Add your resource to **/mobile/java/ExApp/src/main/resource/res/** , such as audio or image etc.     
   * Configure **/mobile/java/ExApp/src/main/config.txt** for icon ,version, boot class, etc .     
   * Build ExApp project , it would copy ExApp.jar to **/mobile/assets/resfiles/ExApp.jar**   
   * Install **/binary/ios/MiniPack.ipa** for iPhone device , (Enterprise distrbute version, need Verify app, Setting->General->Device Management->EGLS Technology ltd->Verify App), or **/binary/android/MiniPack.apk** for Android device , These two binary built from **/mobile/iosapp/**  and **/mobile/java/androidapp**, you can build it yourself.    
   * Touch the app icon to open MiniPack app, you would see the ExApp is running (the left of picture).   
     You can touch "exit to AppManager" in ExApp, AppManager is a App maintaince tool (the middle and right of picture), It can start a in-app webserver for upload app, it can download app from a website also .   
    <div align=center><img width="672" height="398"   src="https://raw.githubusercontent.com/digitalgust/miniJVM/master/screenshot/appmgr.png"/></div>   
  
  
  ## Build for desktop platform:     
 * Build java bootclass  **/minijvm/java**  , Maven build jar copy to /binary/lib/minijvm_rt.jar    
 * Build gui class **/desktop/glfw_gui/java** , Maven build jar copy to /binary/libex/glfw_gui.jar     
 * Build console test case class **/test/minijvm_test** , Maven build jar copy to /binary/libex/minijvm_test.jar     
 * Build gui test app class **/test/minijvm_test** , Maven build jar copy to /binary/<platform>/apps/ExApp.jar    
 * Build gui jni dynamic library **/desktop/glfw_gui/c** , Cmake build library copy to /binary/<platform>/libgui.<so | dylib | dll>    
 * Run test script /binary/<platform>/test.<sh | bat>    
 
   
## How to Remote debug:  
  Desktop platform : Run mini_jvm with flag: -Xdebug for debug mode .  
  iOS/Android simulator : change /mobile/c/glfmapp/main.c , set **jvm->jdp_enable = 1** after **jvm_create()** .  
  iOS/Android device : check the device ip address from General Setting -> wifi ->(i).  
  mini_jvm jdwp listen port is 8000.   
   * Intelli idea : open the java project , menu Run .> Edit Configurations , + remote , Transport : socket , Debugger mode : attach , host is your mini_jvm running at host ip and port ,ex. "localhost:8000" .  
   * Eclipse : configuration  like as idea .  
   * Netbeans : open java project ,  menu Debug .> connect to Debugger, Connector : SocketAttach , host is your mini_jvm running at the host and port, ex. "localhost:8000" , Timeout: 10000 .  
  Then you can setup breakpoint or pause mini_jvm and watch variable's value .  
  


## How to use Embed java compiler in mini_jvm:  
   Java Compiler : /binary/libex/janino.jar    
   Usage of compiler can be found in /binary folder   
   the compile command :  
```
win:
mini_jvm -cp ../lib/minijvm_rt.jar;../libex/janino.jar;../libex/commons-compiler.jar org.codehaus.janino.Compiler  ../res/BpDeepTest.java
posix:
./mini_jvm -cp ../lib/minijvm_rt.jar:../libex/janino.jar:../libex/commons-compiler.jar org.codehaus.janino.Compiler  ../res/BpDeepTest.java
```

Janino compiler is not the full java compiler, see [limitation](http://janino-compiler.github.io/janino/#limitations) , like :
```
List<String> list=new ArrayList(); 
list.add("abc");
String s=(String)list.get(0);//can't ignore (String) cast qualifier.   
```   
   


## Related project and technology:   
   [Sun CLDC](http://www.oracle.com/technetwork/java/cldc-141990.html)  :referenced cldc    
   [Miniz](https://github.com/richgel999/miniz) :for read jar files    
   [Glfm](https://github.com/brackeen/glfm) :for cross platform (android/ios) GUI   
   [Nanovg](https://github.com/memononen/nanovg)  :for GUI paint function   
   [Stb](https://github.com/nothings/stb) :for GUI truetype font and image    
   [Glad](https://github.com/Dav1dde/glad)  :for replace openGL/GLES head file   
   [Glfw](https://github.com/glfw/glfw)  :for pc cross platform GUI   
   [Dirent](https://github.com/tronkko/dirent)  :for linux style on win vc file and directory access    
   [Tinycthread](https://github.com/tinycthread/tinycthread)  :for cross platform thread   
   [JRegex](https://github.com/digitalgust/minijvm_third_lib/tree/master/jregex)  :for java String regex match     
   [Janino](http://janino-compiler.github.io/janino/)  :for compile java source file     
   [MiniAudio](https://github.com/dr-soft/miniaudio)  :for java audio playback and capture   
   [Sljit](https://github.com/zherczeg/sljit)  :Platform independent low-level JIT compiler   
   [Awtk-minijvm](https://github.com/zlgopen/awtk-minijvm)  :[AWTK](https://github.com/zlgopen/awtk) cross platform ui bind to minijvm   
   [Mbedtls](https://github.com/ARMmbed/mbedtls)  :Https support by mbedtls
   [Avian](https://github.com/ReadyTalk/avian)  :Some of class files   
   

## Development IDE using:  
  C code:   JetBrains CLion ,Xcode ,Virtual studio .  
  Swift code/Object c:    XCode  .  
  Java code:    Jetbrain Idea, Netbeans  ,jdk  .  
  android project:  Android Studio .

 
## Build GUI application, depend on OpenGL or OpenGLES     
   * iOS/Android system build with GLFM  (/mobile/iosapp/  ,  /mobile/androidapp/)       
   * Window system build with GLFW   (/desktop/glfw_gui/)      
   * GUI build with Nanovg          
   * GUI based on OpenGL 3.3 and OpenGLES 3.0 as default
  
## Example of mobile application

The example demonstrate how develop java app for iOS and Android 
UI layout xml file MyForm.xml

```
<form name="FORM_MAIN" w="100%" h="100%">
    <script>
        <![CDATA[
        sub change()
            red=mod(random(),255)
            green=mod(random(),255)
            blue=mod(random(),255)
            setColor("LAB_HELP",red,green,blue,255)
            setText("LAB_HELP","Any a test")
        ret
        ]]>
    </script>

    <frame name="FRAME_TEST" w="80%" h="500" align="top,hcenter" title="WINDOW">
        <label name="LAB_HELP" w="100%" h="30" align="hcenter,vcenter">Help text:</label>
        <input w="100%" h="395" multiline="1" edit="0"><![CDATA[
            This app is an example of mini_jvm, Threre are a menu and a frame .
            Touch the 'Exit to AppManager' , you will enter the AppManager, AppManager manage all app, it can upload ,download , delete app.
            1. DOWNLOAD : Put your jar in a website , then input the url of jar in AppManager, Touch 'Download' ,it would download the jar ,then update the app list.
            2. UPLOAD : The first you touch the 'Start' to open the inapp webserver, then open browser in your Desktop Computer, open 'http://phone_ip_addr:8088' , and pickup a jar in the page, upload it. NOTE: That computer and the phone must be same LAN.
            3. RUN : Touch the App name in the list, Touch 'Run' can start the app.
            4. SET AS BOOT APP : The boot app will startup when MiniPack opend.
            5. UPGRADE : AppManager will download the new jar ,url that get from config.txt in jar.
            6. DELETE : The app would be deleteted.;
            ]]>
        </input>
        <br/>
        <button name="BT_SCRIPT" h="40" onclick="change()">{Change}</button>
        <button name="BT_CANCEL" h="40">{Cancel}</button>
        <br/>
    </frame>

    <menu name="MENU_MAIN" x="0" y="90%" w="100%" h="10%" fixed="1">
        <mi name="MI_OPENFRAME" pic="/res/hello.png">{Test}</mi>
        <mi name="MI_EXIT" pic="/res/appmgr.png">{Exit}</mi>
    </menu>
</form>
```

Java source file MyApp.java
```
package test;

import org.mini.apploader.AppManager;
import org.mini.gui.*;
import org.mini.layout.UITemplate;
import org.mini.layout.XContainer;
import org.mini.layout.XEventHandler;

/**
 * @author gust
 */
public class MyApp extends GApplication {

    GForm form;
    GMenu menu;
    GFrame gframe;

    @Override
    public GForm getForm() {
        if (form != null) {
            return form;
        }
        //set the default language
        GLanguage.setCurLang(GLanguage.ID_CHN);

        //load xml
        String xmlStr = GToolkit.readFileFromJarAsString("/res/MyForm.xml", "utf-8");

        UITemplate uit = new UITemplate(xmlStr);
        UITemplate.getVarMap().put("Cancel", "CANCEL"); //replace keywork in xml
        UITemplate.getVarMap().put("Change", "Change");
        UITemplate.getVarMap().put("Test", "test");
        UITemplate.getVarMap().put("Exit", "QUIT");
        XContainer xc = (XContainer) XContainer.parseXml(uit.parse());
        int screenW = GCallBack.getInstance().getDeviceWidth();
        int screenH = GCallBack.getInstance().getDeviceHeight();

        //build gui with event handler
        xc.build(screenW, screenH, new XEventHandler() {
            public void action(GObject gobj, String cmd) {
                String name = gobj.getName();
                switch (name) {
                    case "MI_OPENFRAME":
                        if (form.findByName("FRAME_TEST") == null) {
                            form.add(gframe);
                        }
                        break;
                    case "MI_EXIT":
                        AppManager.getInstance().active();
                        break;
                    case "BT_CANCEL":
                        gframe.close();
                        break;
                }
            }

            public void onStateChange(GObject gobj, String cmd) {
            }
        });
        form = (GForm) xc.getGui();
        gframe = (GFrame) form.findByName("FRAME_TEST");
        if (gframe != null) gframe.align(GGraphics.HCENTER | GGraphics.VCENTER);
        menu = (GMenu) form.findByName("MENU_MAIN");

        //process Hori screen or Vert screen
        //if screen size changed ,then ui will resized relative
        form.setSizeChangeListener((width, height) -> {
            if (gframe != null && gframe.getXmlAgent() != null) {
                ((XContainer) form.getXmlAgent()).reSize(width, height);
                gframe.align(GGraphics.HCENTER | GGraphics.VCENTER);
            }
        });
        return form;
    }
}

```
<div align=center><img width="224" height="398" src="/screenshot/myapp.jpg"/></div>


##   Screen shot   :   
  * Windows mini_jvm gui    
  <div align=center><img width="433" height="336" src="https://raw.githubusercontent.com/digitalgust/miniJVM/master/screenshot/win.png"/></div>
  * Macos mini_jvm gui    
  <div align=center><img width="433" height="336" src="https://raw.githubusercontent.com/digitalgust/miniJVM/master/screenshot/mac.png"/></div> 
  * Linux mini_jvm gui    
  <div align=center><img width="433" height="336" src="https://raw.githubusercontent.com/digitalgust/miniJVM/master/screenshot/centos.png"/></div>


## Directories: 
> /   
>> binary/-------- minijvm binary  for build(win32/win64/mac/linux/android/ios)  
>> minijvm/    
>>> c/------------ minijvm c source    
>>> java/--------- minijvm runtime library     
>>
>> desktop/   
>>> glfw_gui/------ desktop computer gui/audio native module   
>>
>> mobile/        
>>> c/------------- java native lib, glfm framework, gui jni, glfmapp    
>>> java/glfm_gui-- mobile platform native gui lib    
>>> java/ExApp----- java app entry point    
>>> iosapp/-------- iOS launcher     
>>> androidapp/---- Android launcher     
>>> assets/resfiles/- mobile app resource, font files, jar files ,pic ,audio etc.  
>>
>> test/   
>>> jni_test/------ jni example    
>>> jvm_ios/------ ios swift test project       
>>> jvm_macos/---- macosX test project      
>>> jvm_vs/------- windows virtual studio test project      
>>> minijvm_test/-- test case of **/minijvm/java**      
  
     
  
## License
License:	MIT


Gust , digitalgust@163.com , works at EGLS ltd. EGLS is a game development and distribution company .
