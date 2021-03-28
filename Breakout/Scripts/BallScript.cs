using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallScript : MonoBehaviour
{
    public float speed = 5f;
    public float minSpd = 5f;
    public float maxSpd = 10f;
    
    Rigidbody myRigidbody;
    Transform myTransform;
    
    public AudioClip bound_sound;
    public AudioClip bar_sound;
    public AudioClip delete_sound;
    AudioSource audioSource;

    void Start()
    {
        myRigidbody = GetComponent<Rigidbody>();
        myRigidbody.velocity = new Vector3(speed, 0f, speed);
        myTransform = transform;
        audioSource = GetComponent<AudioSource>();
    }
    
    void Update()
    {
        Vector3 velocity = myRigidbody.velocity;
        float clampedSpd = Mathf.Clamp(velocity.magnitude, minSpd, maxSpd);
        myRigdbody.velocity = velocity.normalized * clampedSpd;
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.CompareTag("Bar"))
        {
            Vector3 barPos = collision.transform.position;
            Vector3 ballPos = myTransform.position;
            Vector3 direction = (ballPos - barPos).normalized;
            
            float speed = myRigidbody.velocity.magnitude;
            myRigidbody.velocity = direction * speed;
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
