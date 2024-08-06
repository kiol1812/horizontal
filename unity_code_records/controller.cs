using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

#if !UNITY_EDITOR
using Windows.Networking;
using Windows.Networking.Sockets;
using Windows.Storage.Streams;
#endif

public class controller : MonoBehaviour
{
    public String _input = "45,45";
    public float _x, _y;

    [SerializeField]
    public TMP_Text ConnectButtonText;

    [SerializeField]
    private GameObject _title;
    // private Text _title;

    [SerializeField]
    private GameObject _cube;

#if !UNITY_EDITOR
    StreamSocket socket;
    StreamSocketListener listener;
    String port;
    String message;
#endif

    void Start()
    {
    }
    #region Button Callback
    public void StartListening()
    {
#if !UNITY_EDITOR
        listener = new StreamSocketListener();
        port = "9090";
        listener.ConnectionReceived += Listener_ConnectionReceived;
        listener.Control.KeepAlive = false;

        Listener_Start();
#endif
    }
    #endregion

#if !UNITY_EDITOR
    private async void Listener_Start()
    {
        Debug.Log("Listener started");
        try
        {
            await listener.BindServiceNameAsync(port);
            _input = "Listening";
            ConnectButtonText = "Listening";
        }
        catch (Exception e)
        {
            Debug.Log("Error: " + e.Message);
            _input = "bindError" + e.Message;
        }

        Debug.Log("Listening");
    }

    private async void Listener_ConnectionReceived(StreamSocketListener sender, StreamSocketListenerConnectionReceivedEventArgs args)
    {
        Debug.Log("Connection received");
        // _input = "connected";
        ConnectButtonText = "connected";
        try
        {
            while (true)
            {

                using (var dw = new DataWriter(args.Socket.OutputStream))
                {
                    dw.WriteString(_input); //change "hello there" to _input for debug
                    await dw.StoreAsync();
                    dw.DetachStream();
                }

                using (var dr = new DataReader(args.Socket.InputStream))
                {
                    dr.InputStreamOptions = InputStreamOptions.Partial;
                    await dr.LoadAsync(5);
                    var input = dr.ReadString(5);
                    Debug.Log("received: " + input);
                    _input = input;

                }
            }
        }
        catch (Exception e)
        {
            Debug.Log("disconnected!!!!!!!! " + e);
            ConnectButtonText = "strat listening";
            // _input = e.Message;
        }

    }
#endif
    void process()
    {
        String[] xy = _input.Split(',');
        if (xy.Length == 2)
        {
            _x = float.Parse(xy[0]);
            _y = float.Parse(xy[1]);
        }
    }

    void Update()
    {
        process();
        _cube.transform.eulerAngles = new Vector3(
            _x,
            0,
            _y
        );
        _title.GetComponent<TextMesh>().text = "(" + _input + ")";
    }
}
