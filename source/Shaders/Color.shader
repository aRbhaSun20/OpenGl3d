#shader vertex
#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 texCoord;
layout(location = 2) in vec3 aNormal;

out vec3 u_FragPos;
out vec3 u_Normal;
out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat3 u_NormalizedModel;
uniform mat4 u_MVP;

void main()
{
  u_FragPos = vec3(u_Model*aPos);
  u_Normal = u_NormalizedModel * aNormal;
  gl_Position = u_MVP * aPos;

  v_TexCoord = texCoord;
};

#shader fragment
#version 330 core
 
layout (location = 0) out vec4 FragColor;

in vec2 v_TexCoord;
in vec3 u_Normal;
in vec3 u_FragPos;

struct Ambient_Components{
  vec3 ambientStrength;
  vec3 ambientIntensity;
};

struct Diffuse_Components{
  vec3 diffuseStrength; 
  vec3 diffuseIntensity;
  
} diffuseComp;

struct Specular_Components{
  vec3 specularStrength;  
  float specularShininess; 
  vec3 specularIntensity;
  
} specularComp;

struct Point_SourceProp{
  float constant_Pointsource;
  float linear_Pointsource;
  float quadratic_Pointsource;
} pointSource;

struct Spot_SourceProp{
  vec3 direction;
  float cutOff;
  float outerCutOff;
} spotSource;

struct Material{
 Ambient_Components ambientComp;
 Diffuse_Components diffuseComp;
 Specular_Components specularComp;
 Point_SourceProp pointSource;
 Spot_SourceProp spotSource;
 sampler2D diffuseTexture;
sampler2D specularTexture;
};

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

uniform int lightType;
uniform Material u_Material;
uniform vec3 u_Color;

vec3 getDiffuseTextureMapping()
{
  return vec3(texture(u_Material.diffuseTexture, v_TexCoord ).rgb);
}

vec3 getSpecularTextureMapping()
{
  return vec3(texture(u_Material.specularTexture,v_TexCoord).rgb);
}

vec3 pointLight()
{	
  // ambient
  // vec3 ambient = u_Material.ambientComp.ambientIntensity * u_Material.ambientComp.ambientStrength;
  vec3 ambient = u_Material.ambientComp.ambientIntensity * getDiffuseTextureMapping();

  // diffuse
  vec3 norm = normalize(u_Normal);
  vec3 lightDir = normalize(u_lightPos - u_FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  // vec3 diffuse = u_Material.diffuseComp.diffuseIntensity * (diff * u_Material.diffuseComp.diffuseStrength);
  vec3 diffuse = u_Material.diffuseComp.diffuseIntensity * (diff * getDiffuseTextureMapping());

  // specular
  vec3 viewDir = normalize(u_viewPos - u_FragPos);
  vec3 reflectDir = reflect( -lightDir, norm);
  float spec = pow(max(dot(viewDir , reflectDir), 0.0), u_Material.specularComp.specularShininess);
  vec3 specular = u_Material.specularComp.specularIntensity * (spec * getSpecularTextureMapping());
  
  float distance = length(u_lightPos - u_FragPos);
  float attenuation = 1.0 / (u_Material.pointSource.constant_Pointsource + u_Material.pointSource.linear_Pointsource * distance + u_Material.pointSource.quadratic_Pointsource * (distance * distance));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

	return(ambient + diffuse + specular);
}

vec3 direcLight()
{
  // ambient
  // vec3 ambient = u_Material.ambientComp.ambientIntensity * u_Material.ambientComp.ambientStrength;
  vec3 ambient = u_Material.ambientComp.ambientIntensity * getDiffuseTextureMapping();

  // diffuse
  vec3 norm = normalize(u_Normal);
  vec3 lightDir = normalize(u_lightPos - u_FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  // vec3 diffuse = u_Material.diffuseComp.diffuseIntensity * (diff * u_Material.diffuseComp.diffuseStrength);
  vec3 diffuse = u_Material.diffuseComp.diffuseIntensity * (diff * getDiffuseTextureMapping());

  // specular
  vec3 viewDir = normalize(u_viewPos - u_FragPos);
  vec3 reflectDir = reflect( -lightDir, norm);
  float spec = pow(max(dot(viewDir , reflectDir), 0.0), u_Material.specularComp.specularShininess);
  vec3 specular = u_Material.specularComp.specularIntensity * (spec * getSpecularTextureMapping());
  
	return(ambient + diffuse + specular);
}

vec3 spotLight()
{
    vec3 lightDir = normalize(u_lightPos - u_FragPos);
    
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-u_Material.spotSource.direction)); 
    
    if(theta > u_Material.spotSource.cutOff) // remember that we're working with angles as cosines instead of degrees so a '>' is used.
    {      
      // ambient
      // vec3 ambient = u_Material.ambientComp.ambientIntensity ;
      vec3 ambient = u_Material.ambientComp.ambientIntensity 
        * getDiffuseTextureMapping() * u_Material.ambientComp.ambientStrength;
    
      // diffuse
      vec3 norm = normalize(u_Normal);
      float diff = max(dot(norm, lightDir), 0.0);
      // vec3 diffuse = u_Material.diffuseComp.diffuseIntensity * (diff * u_Material.diffuseComp.diffuseStrength);
      vec3 diffuse = u_Material.diffuseComp.diffuseIntensity * (diff * getDiffuseTextureMapping());
    
      // specular
      vec3 viewDir = normalize(u_viewPos - u_FragPos);
      vec3 reflectDir = reflect( -lightDir, norm);
      float spec = pow(max(dot(viewDir , reflectDir), 0.0), u_Material.specularComp.specularShininess);
      vec3 specular = u_Material.specularComp.specularIntensity * (spec * getSpecularTextureMapping());
      
      float distance = length(u_lightPos - u_FragPos);
      float attenuation = 1.0 / (u_Material.pointSource.constant_Pointsource 
        + u_Material.pointSource.linear_Pointsource * distance 
        + u_Material.pointSource.quadratic_Pointsource * (distance * distance));
    
      diffuse *= attenuation;
      specular *= attenuation;
          
      return(vec3(ambient + diffuse + specular));
    }
    else 
    {
      // else, use ambient light so scene isn't completely dark outside the spotlight.
      return(vec3(u_Material.ambientComp.ambientIntensity * getDiffuseTextureMapping())); 
    }
}

vec3 spotSmoothLight(){
  // ambient
      // vec3 ambient = u_Material.ambientComp.ambientIntensity * u_Material.ambientComp.ambientStrength;
      vec3 ambient = u_Material.ambientComp.ambientIntensity * getDiffuseTextureMapping();
    
      // diffuse
      vec3 norm = normalize(u_Normal);
      vec3 lightDir = normalize(u_lightPos - u_FragPos);
      float diff = max(dot(norm, lightDir), 0.0);
      // vec3 diffuse = u_Material.diffuseComp.diffuseIntensity * (diff * u_Material.diffuseComp.diffuseStrength);
      vec3 diffuse = u_Material.diffuseComp.diffuseIntensity * (diff * getDiffuseTextureMapping());
    
      // specular
      vec3 viewDir = normalize(u_viewPos - u_FragPos);
      vec3 reflectDir = reflect( -lightDir, norm);
      float spec = pow(max(dot(viewDir , reflectDir), 0.0), u_Material.specularComp.specularShininess);
      vec3 specular = u_Material.specularComp.specularIntensity * (spec * getSpecularTextureMapping());
      
       // spotlight (soft edges)
      float theta = dot(lightDir, normalize(-u_Material.spotSource.direction)); 
      float epsilon = (u_Material.spotSource.cutOff - u_Material.spotSource.outerCutOff);
      float intensity = clamp((theta - u_Material.spotSource.outerCutOff) / epsilon, 0.0, 1.0);
      diffuse  *= intensity;
      specular *= intensity;

      // attenuation
      float distance = length(u_lightPos - u_FragPos);
      float attenuation = 1.0 / (u_Material.pointSource.constant_Pointsource 
      + u_Material.pointSource.linear_Pointsource * distance + 
      u_Material.pointSource.quadratic_Pointsource * (distance * distance));
    
      ambient  *= attenuation; 
      diffuse  *= attenuation;
      specular *= attenuation; 
      
      return(vec3(ambient + diffuse + specular));
}

void main()
{
  if(lightType == 1){
      vec3 result = pointLight();
      FragColor = vec4(result , 1.0);  
  }  
  else if(lightType == 2){
      vec3 result = direcLight();
      FragColor = vec4(result , 1.0);  
  }  
  else if(lightType == 3){
      vec3 result = spotLight();
      FragColor = vec4(result , 1.0);  
  }  
  else if(lightType == 4){
      vec3 result = spotSmoothLight();
      FragColor = vec4(result , 1.0);  
  }
  else{
      FragColor = vec4(u_Color, 1.0);
  }
  // vec4 texColor = mix(texture(texture1, v_TexCoord), texture(texture2, v_TexCoord), 0.2);
};
