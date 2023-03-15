// Loop through chunks in reverse (from most significant to least significant)
for (uint64_t i = chunk_count; i >= 0; i--)
{
	// Step 4: Estimate the quotient using the most significant digits
	// Clamp the estimate to the maximum value of a single digit (9)
	// Step 5: Refine the estimated quotient and compute the remainder
	// Adjust the estimate if necessary
	// Update the dividend with the remainder
	// Save the quotient for this chunk
}