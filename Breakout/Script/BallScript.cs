using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallScript : MonoBehaviour
{
    public float speed = 5f;
    Rigidbody myRigidbody;
    public AudioClip bound_sound;
    public AudioClip bar_sound;
    public AudioClip delete_sound;
    AudioSource audioSource;

    void Start()
    {
        myRigidbody = GetComponent<Rigidbody>();
        myRigidbody.velocity = new Vector3(speed, 0f, speed);
        audioSource = GetComponent<AudioSource>();
    }

    private void OnCollisionEnter(Collision collision)
    {
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
