using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cubetest : MonoBehaviour
{
    Plane plane;
    bool isGrabbing;
    Transform cube;

    // Start is called before the first frame update
    void Start()
    {
        plane = new Plane(Vector3.up, Vector3.up);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

            RaycastHit hit;
            if(Physics.Raycast(ray, out hit, Mathf.Infinity))
            {
                if(hit.collider.tag == "Player")
                {
                    isGrabbing = true;
                    cube = hit.transform;
                }
            }
        }

        if (isGrabbing)
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            float rayDistance;
            plane.Raycast(ray, out rayDistance);

            cube.position = ray.GetPoint(rayDistance);

            if (Input.GetMouseButtonUp(0))
            {
                isGrabbing = false;
            }
        }
    }
}
