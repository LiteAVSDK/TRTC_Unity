using System;
using UnityEngine;

public class BackGroundMusicHelper : MonoBehaviour {
  private AudioSource source;
  private static BackGroundMusicHelper sInstance;
  private static readonly System.Object sLock = new System.Object();
  public void Awake() {
    DontDestroyOnLoad(gameObject);
    installBackGround();
  }

  private BackGroundMusicHelper() {
    UnityEngine.Debug.LogFormat("BackGroundMusicHelper: install menthod");
  }
  public void installBackGround() {
    source = this.gameObject.AddComponent<AudioSource>();
    source.loop = true;
    AudioClip ac = Resources.Load<AudioClip>("test3");
    source.clip = ac;
    UnityEngine.Debug.LogFormat("installBackGround ");
  }

  public AudioSource getAudioSoucre() { return source; }
  public static BackGroundMusicHelper getInstanceGroundMusicHelper() {
    lock (sLock) {
      if (sInstance == null) {
        GameObject obj = new GameObject("BackGroundMusicHelper");
        obj.hideFlags = HideFlags.HideAndDontSave;
        DontDestroyOnLoad(obj);
        sInstance = obj.AddComponent<BackGroundMusicHelper>();
        UnityEngine.Debug.LogFormat("BackGroundMusicHelper:{0},{1}", obj.GetInstanceID(),
                                    sInstance);
      }
      return sInstance;
    }
  }

  public static bool DestroyBackGroundMusicHelper() {
    lock (sLock) {
      if (sInstance) {
        if (sInstance.gameObject) {
          Destroy(sInstance.gameObject);
        }
        Destroy(sInstance);

        UnityEngine.Debug.LogFormat("DestroyThreadHelper:{0},{1}", sInstance.gameObject, sInstance);
      }
      return true;
    }
    return false;
  }
}
