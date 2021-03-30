using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallScript : MonoBehaviour
{
    public float speed = 5f;
    public float minSpd = 5f;
    public float maxSpd = 10f;
    public bool start;

    Rigidbody myRigidbody;
    Transform myTransform;
    BarControl barcontrol;

    public AudioClip bound_sound;
    public AudioClip bar_sound;
    public AudioClip delete_sound;
    AudioSource audioSource;

    void Start()
    {
        start = false;

        //barcontrol = GameObject.Find("Bar").GetComponent<BarControl>();

        myRigidbody = GetComponent<Rigidbody>();
        myTransform = transform;         //初期位置はバーと同じ位置
        audioSource = GetComponent<AudioSource>();
    }

    void Update()
    {
        if (Input.GetMouseButtonDown(0) && !start)
        {
            myRigidbody.velocity = new Vector3(speed, 0f, speed);   //ボールの発射
            start = true;

        }
        else //初期位置以外の場合、バーを自由に動かせるようにする
        {
            Vector3 velocity = myRigidbody.velocity;
            float clampedSpd = Mathf.Clamp(velocity.magnitude, minSpd, maxSpd);
            myRigidbody.velocity = velocity.normalized * clampedSpd;
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("Bar"))
        {
            Vector3 barPos = collision.transform.position;      //Barの位置を取得
            Vector3 ballPos = myTransform.position;             //ボールの位置を取得
            Vector3 direction = (ballPos - barPos).normalized;  //Barから見たボールの方向を計算

            float speed = myRigidbody.velocity.magnitude;       //現在の速さを取得
            myRigidbody.velocity = direction * speed;           //速度を変更
        }

        if(collision.gameObject.tag == "Wall")
        {
            audioSource.PlayOneShot(bound_sound);
        }

        if(collision.gameObject.tag == "Bar")
        {
            audioSource.PlayOneShot(bar_sound);
        }

        if(collision.gameObject.tag == "Block")
        {
            audioSource.PlayOneShot(delete_sound);
        }
    }
}
