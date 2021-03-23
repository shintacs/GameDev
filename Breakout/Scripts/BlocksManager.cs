using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BlocksManager : MonoBehaviour
{
    Transform myTransform;
    public bool deleteBlock;

    void Start()
    {
        myTransform = transform;
        deleteBlock = false;
    }

    void Update()
    {
        if(myTransform.childCount == 0)
        {
            deleteBlock = true;
            Time.timeScale = 0f;
        }
    }
}
