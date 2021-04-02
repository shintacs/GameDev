using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlockScript : MonoBehaviour
{
    [SerializeField]
    public bool item_star;

    private void Start()
    {
        item_star = false;
    }

    void OnCollisionEnter(Collision collision)
    {
        if (gameObject.name == "Block_star")
        {
            item_star = true;
        }

        DestroyBlock();

    }

    private void DestroyBlock()
    {
        Destroy(gameObject);
;    }
}
