#version 400

out vec4 fragColor;

// Uniforms
uniform float angle; // Moon's angle in radians (0 = horizon, π/2 = zenith, π = opposite horizon)

void main()
{
    const float horizonRange = 0.1; // Range near the horizon for smooth transitions

    // Define colors for the moon
    vec3 moonRiseColor = vec3(0.9, 0.9, 1.0); // Soft bluish-white
    vec3 moonHighColor = vec3(1.0, 1.0, 1.0); // Bright white
    vec3 moonSetColor = vec3(0.7, 0.7, 0.8);  // Dim bluish

    // Compute transition factor based on moon's angle
    float moonTransitionFactor = clamp((sin(angle) + 1.0) / 2.0, 0.0, 1.0);

    // Determine moon color
    vec3 moonColor;
    if (angle > 0.0 && angle <= 3.14159265 / 2.0) { // Moonrise to high
        moonColor = mix(moonRiseColor, moonHighColor, moonTransitionFactor);
    } else if (angle > 3.14159265 / 2.0 && angle <= 3.14159265) { // High to moonset
        moonColor = mix(moonHighColor, moonSetColor, moonTransitionFactor);
    } else {
        // Below the horizon
        moonColor = vec3(0.0, 0.0, 0.0);
    }

    // Set the output color
    fragColor = vec4(moonColor, 1.0); // Alpha is 1.0 (opaque)
}