package java.Adapter;

public class Demo {
    /**
     * 为媒体播放器和更高级的媒体播放器创建接口。
     * 创建实现了 AdvancedMediaPlayer 接口的实体类
     * 创建实现了 MediaPlayer 接口的适配器类
     * 创建实现了 MediaPlayer 接口的实体类。里面用的是适配器
     * 使用 AudioPlayer 来播放不同类型的音频格式。
     * @param args
     */
    public static void main(String[] args) {
        AudioPlayer audioPlayer = new AudioPlayer();
   
        audioPlayer.play("mp3", "beyond the horizon.mp3");
        audioPlayer.play("mp4", "alone.mp4");
        audioPlayer.play("vlc", "far far away.vlc");
        audioPlayer.play("avi", "mind me.avi");
     }
}
