using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RayCheck : MonoBehaviour
{
    void Start()
    {
        
    }

    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Raycheck();
        }
    }

    private void Raycheck()
    {
        RaycastHit rayhit;
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        if(Physics.Raycast(ray, out rayhit, Mathf.Infinity))
        {
            Debug.DrawRay(ray.origin, ray.direction * 100, Color.red, 5);
            if(rayhit.collider.tag == "Bar")
            {
                print("hit!");
            }
        }
    }
}
