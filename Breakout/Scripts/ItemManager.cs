using UnityEngine;

public class ItemManager : MonoBehaviour
{
    //[SerializeField]
    GameObject Star;
    BlockScript blockscript;

    void Start()
    {
        Star = GameObject.FindWithTag("Star");
        blockscript = GameObject.Find("Block_star").GetComponent<BlockScript>();
        Star.SetActive(false);
    }

    void Update()
    {
        if (blockscript.item_star)
        {
            Star.SetActive(true);
            Star.transform.Translate(0f, 0f, -0.02f);
        }
    }
}
