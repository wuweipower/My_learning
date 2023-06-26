package java.Adapter;

public class MediaAdapter implements MediaPlayer{
    AdvancedMediaPlayer advancedMediaPlayer;
    public MediaAdapter(String type)
    {
        if(type.equalsIgnoreCase("vlc"))
        {
            advancedMediaPlayer = new VlcPlayer();
        }else if(type.equalsIgnoreCase("mp4"))
        {
            advancedMediaPlayer = new Mp4Player();
        }

    }
    public void play(String audioType,String filname)
    {
        if(audioType.equalsIgnoreCase("vlc"))
        {
            advancedMediaPlayer.playVlc(filname);
        }else if(audioType.equalsIgnoreCase("mp4"))
        {
            advancedMediaPlayer.palyMp4(filname);
        }
    }
}
