def blend_black_with_light_hex(light_hex, intensity):
    # Convert hex light color to RGB
    light_rgb = [int(light_hex[i:i+2], 16) for i in (1, 3, 5)]
    
    # Black is always (0, 0, 0)
    black_rgb = (0, 0, 0)
    
    # Calculate the blended RGB values using linear interpolation
    blended_rgb = [
        int((1 - intensity) * black_rgb[i] + intensity * light_rgb[i]) 
        for i in range(3)
    ]
    
    # Convert RGB back to hex
    blended_hex = '#' + ''.join(f'{x:02X}' for x in blended_rgb)
    return blended_hex

# Example usage
light_hex = "#97B11C"  # Red light
intensity = 0.15  # 50% intensity

blended_color = blend_black_with_light_hex(light_hex, intensity)
print(blended_color)  # Output will be a hex color code for blended color
