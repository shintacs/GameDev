using UnityEngine;

public class ItemManager : MonoBehaviour
{
    //[SerializeField]
    GameObject Star;
    BlockScript blockscript;
    Rigidbody StarRigidbody;

    void Start()
    {
        Star = GameObject.FindWithTag("Star");
        StarRigidbody = Star.GetComponent<Rigidbody>();
        blockscript = GameObject.Find("Block_star").GetComponent<BlockScript>();
        Star.SetActive(false);
    }

    void Update()
    {
        if (blockscript.item_star)
        {
            Star.SetActive(true);
            StarRigidbody.velocity = new Vector3(0f, 0f, -0.02f);
        }
    }
}
