using Google.Protobuf.Protocol;

public class SceneDataManager
{
    private S_LOGIN _loginPkt;
    public S_LOGIN LoginPkt
    {
        get { return _loginPkt; }
        set { _loginPkt = value; }
    }

    private S_ENTER _enterPkt;
    public S_ENTER EnterPkt
    {
        get { return _enterPkt; }
        set { _enterPkt = value; }
    }

}