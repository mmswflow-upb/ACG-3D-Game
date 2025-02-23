#version 400

out vec4 fragColor;

// Uniforms
uniform float angle; // Sun's angle in radians (0 = horizon, π/2 = zenith, π = opposite horizon)

void main()
{
    const float horizonRange = 0.1; // Range near the horizon for smooth transitions

    // Define colors for the sun
    vec3 sunDawnColor = vec3(1.0, 0.5, 0.0);  // Orange
    vec3 sunNoonColor = vec3(1.0, 1.0, 1.0);  // White
    vec3 sunDuskColor = vec3(1.0, 0.5, 0.0);  // Orange

    // Compute transition factor based on sun's angle
    float sunTransitionFactor = clamp((sin(angle) + 1.0) / 2.0, 0.0, 1.0);

    // Determine sun color
    vec3 sunColor;
    if (angle > 0.0 && angle <= 3.14159265 / 2.0) { // Dawn to noon
        sunColor = mix(sunDawnColor, sunNoonColor, sunTransitionFactor);
    } else if (angle > 3.14159265 / 2.0 && angle <= 3.14159265) { // Noon to dusk
        sunColor = mix(sunNoonColor, sunDuskColor, sunTransitionFactor);
    } else {
        // Below the horizon
        sunColor = vec3(0.0, 0.0, 0.0);
    }

    // Set the output color
    fragColor = vec4(sunColor, 1.0); // Alpha is 1.0 (opaque)
}
