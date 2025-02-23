#version 400

in vec2 textureCoord; 
in vec3 norm;
in vec3 fragPos;

out vec4 fragColor;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    // Ambient light
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse light
    vec3 normal = normalize(norm);
    vec3 lightDir = normalize(lightPos - fragPos); 
    float diff = max(dot(normal, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    // Specular light
    float specularStrength = 0.7;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine lighting components
    vec3 lighting = ambient + diffuse + specular;

    // Sample texture color
    vec4 texColor = texture(texture1, textureCoord);

    // Add a blue tint and transparency
    vec3 blueTint = vec3(0.2, 0.4, 0.8); // Blue color (adjust for desired tint)
    float alpha = 0.8; // Transparency level (0.0 = fully transparent, 1.0 = fully opaque)

    // Combine lighting, texture, and blue tint
    vec3 finalColor = mix(texColor.rgb, blueTint, 0.5) * lighting;

    fragColor = vec4(finalColor, alpha); // Output final color with transparency
}
