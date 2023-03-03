using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public float growthFactor = 0.1f; // The amount by which the player grows on collision
    public float shrinkFactor = 0.1f; // The amount by which the enemy shrinks on collision

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Enemy"))
        {
            // Make player bigger
            transform.localScale += new Vector3(growthFactor, growthFactor, 0);

            // Make enemy smaller
            collision.transform.localScale -= new Vector3(shrinkFactor, shrinkFactor, 0);
        }
    }
}
