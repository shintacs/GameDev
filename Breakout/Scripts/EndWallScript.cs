using UnityEngine;

public class EndWallScript : MonoBehaviour
{
    public bool hitBall;
    public int hitball_cnt;

    void Start()
    {
        hitBall = false;
    }

    void OnCollisionEnter(Collision collision)
    {
        hitBall = true;
        hitball_cnt += 1;
        Destroy(collision.gameObject);
    }
}
