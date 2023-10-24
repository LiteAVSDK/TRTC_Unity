using System;
using System.Runtime.InteropServices;

namespace trtc
{
    [StructLayout(LayoutKind.Sequential)]
    public struct TRTCInnerMixUser
    {
        public string userId;
        
        public string roomId;
        
        public RECT rect;
        
        public int zOrder;
        
        public TRTCVideoStreamType streamType;
        
        public byte pureAudio;
        
        public TRTCMixInputType inputType;

        public UInt32 renderMode;

        public UInt32 soundLevel;
    
        public string image;
    }

    public class TRTCTypeConverter
    {
        public static TRTCInnerMixUser ConvertTRTCMixUser(TRTCMixUser user)
        {
            TRTCInnerMixUser innerMixUser = new TRTCInnerMixUser();
            innerMixUser.userId = user.userId;
            innerMixUser.roomId = user.roomId;
            innerMixUser.rect = user.rect;
            innerMixUser.zOrder = user.zOrder;
            innerMixUser.streamType = user.streamType;
            innerMixUser.pureAudio = (byte)(user.pureAudio ? 1 : 0);
            innerMixUser.inputType = user.inputType;
            innerMixUser.renderMode = user.renderMode;
            innerMixUser.soundLevel = user.soundLevel;
            innerMixUser.image = user.image;
            return innerMixUser;
        }
    }

}