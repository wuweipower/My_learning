package java.Adapter;

public class AudioPlayer implements MediaPlayer{
    public void play(String audioType,String filename)
    {
        MediaAdapter mediaAdapter; 
        if(audioType.equalsIgnoreCase("mp3")){
            System.out.println("Playing mp3 file. Name: "+ filename);         
         } 
         //mediaAdapter 提供了播放其他文件格式的支持
         else if(audioType.equalsIgnoreCase("vlc") 
            || audioType.equalsIgnoreCase("mp4")){
            mediaAdapter = new MediaAdapter(audioType);
            mediaAdapter.play(audioType, filename);
         }
         else{
            System.out.println("Invalid media. "+
               audioType + " format not supported");
         }
    }
}
