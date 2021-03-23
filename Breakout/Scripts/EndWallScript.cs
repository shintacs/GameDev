using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EndWallScript : MonoBehaviour
{
    public bool hitBall;

    void Start()
    {
        hitBall = false;
    }

    void OnCollisionEnter(Collision collision)
    {
        hitBall = true;
        Destroy(collision.gameObject);
    }
}
