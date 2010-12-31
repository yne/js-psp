/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */
      
#ifndef __pspgu_h__
#define __pspgu_h__

#include <psptypes.h>
#include <pspge.h>

/** @defgroup GU Graphics Utility Library
 *
 */

#if defined(__cplusplus)
extern "C" {
#endif

/* PI, float-sized */
#define GU_PI			(3.141593f)

#define GU_FALSE		(0)
#define GU_TRUE			(1)

/* Primitive types */
#define GU_POINTS		(0)
#define GU_LINES		(1)
#define GU_LINE_STRIP		(2)
#define GU_TRIANGLES		(3)
#define GU_TRIANGLE_STRIP	(4)
#define GU_TRIANGLE_FAN		(5)
#define GU_SPRITES		(6)

/* States */
#define GU_ALPHA_TEST		(0)
#define GU_DEPTH_TEST		(1)
#define GU_SCISSOR_TEST		(2)
#define GU_STENCIL_TEST		(3)
#define GU_BLEND		(4)
#define GU_CULL_FACE		(5)
#define GU_DITHER		(6)
#define GU_FOG			(7)
#define GU_CLIP_PLANES		(8)
#define GU_TEXTURE_2D		(9)
#define GU_LIGHTING		(10)
#define GU_LIGHT0		(11)
#define GU_LIGHT1		(12)
#define GU_LIGHT2		(13)
#define GU_LIGHT3		(14)
#define GU_UNKNOWN_15		(15)
#define GU_UNKNOWN_16		(16)
#define GU_COLOR_TEST		(17)
#define GU_COLOR_LOGIC_OP	(18)
#define GU_FACE_NORMAL_REVERSE	(19)
#define GU_PATCH_FACE		(20)
#define GU_FRAGMENT_2X		(21)

/* Matrix modes */
#define GU_PROJECTION		(0)
#define GU_VIEW			(1)
#define GU_MODEL		(2)
#define GU_TEXTURE		(3)

/* Vertex Declarations Begin */
#define GU_TEXTURE_SHIFT(n)	((n)<<0)
#define GU_TEXTURE_8BIT		GU_TEXTURE_SHIFT(1)
#define GU_TEXTURE_16BIT	GU_TEXTURE_SHIFT(2)
#define GU_TEXTURE_32BITF	GU_TEXTURE_SHIFT(3)
#define GU_TEXTURE_BITS		GU_TEXTURE_SHIFT(3)

#define GU_COLOR_SHIFT(n)	((n)<<2)
#define GU_COLOR_RES1		GU_COLOR_SHIFT(1)
#define GU_COLOR_RES2		GU_COLOR_SHIFT(2)
#define GU_COLOR_RES3		GU_COLOR_SHIFT(3)
#define GU_COLOR_5650		GU_COLOR_SHIFT(4)
#define GU_COLOR_5551		GU_COLOR_SHIFT(5)
#define GU_COLOR_4444		GU_COLOR_SHIFT(6)
#define GU_COLOR_8888		GU_COLOR_SHIFT(7)
#define GU_COLOR_BITS		GU_COLOR_SHIFT(7)

#define GU_NORMAL_SHIFT(n)	((n)<<5)
#define GU_NORMAL_8BIT		GU_NORMAL_SHIFT(1)
#define GU_NORMAL_16BIT		GU_NORMAL_SHIFT(2)
#define GU_NORMAL_32BITF	GU_NORMAL_SHIFT(3)
#define GU_NORMAL_BITS		GU_NORMAL_SHIFT(3)

#define GU_VERTEX_SHIFT(n)	((n)<<7)
#define GU_VERTEX_8BIT		GU_VERTEX_SHIFT(1)
#define GU_VERTEX_16BIT		GU_VERTEX_SHIFT(2)
#define GU_VERTEX_32BITF	GU_VERTEX_SHIFT(3)
#define GU_VERTEX_BITS		GU_VERTEX_SHIFT(3)

#define GU_WEIGHT_SHIFT(n)	((n)<<9)
#define GU_WEIGHT_8BIT		GU_WEIGHT_SHIFT(1)
#define GU_WEIGHT_16BIT		GU_WEIGHT_SHIFT(2)
#define GU_WEIGHT_32BITF	GU_WEIGHT_SHIFT(3)
#define GU_WEIGHT_BITS		GU_WEIGHT_SHIFT(3)

#define GU_INDEX_SHIFT(n)	((n)<<11)
#define GU_INDEX_8BIT		GU_INDEX_SHIFT(1)
#define GU_INDEX_16BIT		GU_INDEX_SHIFT(2)
#define GU_INDEX_BITS		GU_INDEX_SHIFT(3)

#define GU_WEIGHTS(n)		((((n)-1)&7)<<14)
#define GU_WEIGHTS_BITS		GU_WEIGHTS(8)
#define GU_VERTICES(n)		((((n)-1)&7)<<18)
#define GU_VERTICES_BITS	GU_VERTICES(8)

#define GU_TRANSFORM_SHIFT(n)	((n)<<23)
#define GU_TRANSFORM_3D		GU_TRANSFORM_SHIFT(0)
#define GU_TRANSFORM_2D		GU_TRANSFORM_SHIFT(1)
#define GU_TRANSFORM_BITS	GU_TRANSFORM_SHIFT(1)
/* Vertex Declarations End */

/* Pixel Formats */
#define GU_PSM_5650		(0) /* Display, Texture, Palette */
#define GU_PSM_5551		(1) /* Display, Texture, Palette */
#define GU_PSM_4444		(2) /* Display, Texture, Palette */
#define GU_PSM_8888		(3) /* Display, Texture, Palette */
#define GU_PSM_T4		(4) /* Texture */
#define GU_PSM_T8		(5) /* Texture */
#define GU_PSM_T16		(6) /* Texture */
#define GU_PSM_T32		(7) /* Texture */
#define GU_PSM_DXT1		(8) /* Texture */
#define GU_PSM_DXT3		(9) /* Texture */
#define GU_PSM_DXT5		(10) /* Texture */

/* Shading Model */
#define GU_FLAT			(0)
#define GU_SMOOTH		(1)

/* Logical operation */
#define GU_CLEAR		(0)
#define GU_AND			(1)
#define GU_AND_REVERSE		(2)
#define GU_COPY			(3)
#define GU_AND_INVERTED		(4)
#define GU_NOOP			(5)
#define GU_XOR			(6)
#define GU_OR			(7)
#define GU_NOR			(8)
#define GU_EQUIV		(9)
#define GU_INVERTED		(10)
#define GU_OR_REVERSE		(11)
#define GU_COPY_INVERTED	(12)
#define GU_OR_INVERTED		(13)
#define GU_NAND			(14)
#define GU_SET			(15)

/* Texture Filter */
#define GU_NEAREST		(0)
#define GU_LINEAR		(1)
#define GU_NEAREST_MIPMAP_NEAREST (4)
#define GU_LINEAR_MIPMAP_NEAREST (5)
#define GU_NEAREST_MIPMAP_LINEAR (6)
#define GU_LINEAR_MIPMAP_LINEAR	(7)

/* Texture Map Mode */
#define GU_TEXTURE_COORDS	(0)
#define GU_TEXTURE_MATRIX	(1)
#define GU_ENVIRONMENT_MAP	(2)

/* Texture Projection Map Mode */
#define GU_POSITION		(0)
#define GU_UV			(1)
#define GU_NORMALIZED_NORMAL	(2)
#define GU_NORMAL		(3)

/* Wrap Mode */
#define GU_REPEAT		(0)
#define GU_CLAMP		(1)

/* Front Face Direction */
#define GU_CW			(0)
#define GU_CCW			(1)

/* Test Function */
#define GU_NEVER		(0)
#define GU_ALWAYS		(1)
#define GU_EQUAL		(2)
#define GU_NOTEQUAL		(3)
#define GU_LESS			(4)
#define GU_LEQUAL		(5)
#define GU_GREATER		(6)
#define GU_GEQUAL		(7)

/* Clear Buffer Mask */
#define GU_COLOR_BUFFER_BIT	(1)
#define GU_STENCIL_BUFFER_BIT	(2)
#define GU_DEPTH_BUFFER_BIT	(4)

/* Texture Effect */
#define GU_TFX_MODULATE		(0)
#define GU_TFX_DECAL		(1)
#define GU_TFX_BLEND		(2)
#define GU_TFX_REPLACE		(3)
#define GU_TFX_ADD		(4)

/* Texture Color Component */
#define GU_TCC_RGB		(0)
#define GU_TCC_RGBA		(1)

/* Blending Op */
#define GU_ADD			(0)
#define GU_SUBTRACT		(1)
#define GU_REVERSE_SUBTRACT	(2)
#define GU_MIN			(3)
#define GU_MAX			(4)
#define GU_ABS			(5)

/* Blending Factor */
#define GU_SRC_COLOR		(0)
#define GU_ONE_MINUS_SRC_COLOR	(1)
#define GU_SRC_ALPHA		(2)
#define GU_ONE_MINUS_SRC_ALPHA	(3)
#define GU_DST_COLOR		(0)
#define GU_ONE_MINUS_DST_COLOR	(1)
#define GU_DST_ALPHA		(4)
#define GU_ONE_MINUS_DST_ALPHA	(5)
#define GU_FIX			(10)

/* Stencil Operations */
#define GU_KEEP			(0)
#define GU_ZERO			(1)
#define GU_REPLACE		(2)
#define GU_INVERT		(3)
#define GU_INCR			(4)
#define GU_DECR			(5)

/* Light Components */
#define GU_AMBIENT		(1)
#define GU_DIFFUSE		(2)
#define GU_SPECULAR		(4)
#define GU_AMBIENT_AND_DIFFUSE	(GU_AMBIENT|GU_DIFFUSE)
#define GU_DIFFUSE_AND_SPECULAR	(GU_DIFFUSE|GU_SPECULAR)
#define GU_UNKNOWN_LIGHT_COMPONENT (8)

/* Light Type */
#define GU_DIRECTIONAL		(0)
#define GU_POINTLIGHT		(1)
#define GU_SPOTLIGHT		(2)

/* Contexts */
#define GU_DIRECT		(0)
#define GU_CALL			(1)
#define GU_SEND			(2)

/* List Queue */
#define GU_TAIL			(0)
#define GU_HEAD			(1)

/** @addtogroup GU */
/*@{*/

/**
  * Set depth buffer parameters
  *
  * @param zbp - VRAM pointer where the depthbuffer should start
  * @param zbw - The width of the depth-buffer (block-aligned)
  *
**/
extern void sceGuDepthBuffer(void* zbp, int zbw);

/**
  * Set display buffer parameters
  *
  * @par Example: Setup a standard 16-bit display buffer
  * @code
  * sceGuDispBuffer(480,272,(void*)512*272*2,512); // 480*272, skipping the draw buffer located at address 0
  * @endcode
  *
  * @param width - Width of the display buffer in pixels
  * @param height - Width of the display buffer in pixels
  * @param dispbp - VRAM pointer to where the display-buffer starts
  * @param dispbw - Display buffer width (block aligned)
  *
**/
extern void sceGuDispBuffer(int width, int height, void* dispbp, int dispbw);

/**
  * Set draw buffer parameters (and store in context for buffer-swap)
  *
  * Available pixel formats are:
  *   - GU_PSM_5650
  *   - GU_PSM_5551
  *   - GU_PSM_4444
  *   - GU_PSM_8888
  *
  * @par Example: Setup a standard 16-bit draw buffer
  * @code
  * sceGuDispBuffer(GU_PSM_5551,(void*)0,512);
  * @endcode
  *
  * @param psm - Pixel format to use for rendering (and display)
  * @param fbp - VRAM pointer to where the draw buffer starts
  * @param fbw - Frame buffer width (block aligned)
**/
extern void sceGuDrawBuffer(int psm, void* fbp, int fbw);

/**
  * Set draw buffer directly, not storing parameters in the context
  *
  * @param psm - Pixel format to use for rendering
  * @param fbp - VRAM pointer to where the draw buffer starts
  * @param fbw - Frame buffer width (block aligned)
**/
extern void sceGuDrawBufferList(int psm, void* fbp, int fbw);

/**
  * Turn display on or off
  *
  * Available states are:
  *   - GU_TRUE (1) - Turns display on
  *   - GU_FALSE (0) - Turns display off
  *
  * @param state - Turn display on or off
  * @returns State of the display prior to this call
**/
extern int sceGuDisplay(int state);

/**
  * Select which depth-test function to use
  *
  * Valid choices for the depth-test are:
  *   - GU_NEVER - No pixels pass the depth-test
  *   - GU_ALWAYS - All pixels pass the depth-test
  *   - GU_EQUAL - Pixels that match the depth-test pass
  *   - GU_NOTEQUAL - Pixels that doesn't match the depth-test pass
  *   - GU_LESS - Pixels that are less in depth passes
  *   - GU_LEQUAL - Pixels that are less or equal in depth passes
  *   - GU_GREATER - Pixels that are greater in depth passes
  *   - GU_GEQUAL - Pixels that are greater or equal passes
  *
  * @param function - Depth test function to use
**/
extern void sceGuDepthFunc(int function);

/**
  * Mask depth buffer writes
  *
  * @param mask - GU_TRUE(1) to disable Z writes, GU_FALSE(0) to enable
**/
extern void sceGuDepthMask(int mask);

extern void sceGuDepthOffset(unsigned int offset);
extern void sceGuDepthRange(int near, int far);
extern void sceGuFog(float near, float far, unsigned int color);

/**
  * Initalize the GU system
  *
  * This function MUST be called as the first function, otherwise state is undetermined.
**/
extern void sceGuInit(void);

/**
  * Shutdown the GU system
  *
  * Called when GU is no longer needed
**/
extern void sceGuTerm(void);

extern void sceGuBreak(int a0);
extern void sceGuContinue(void);
extern void* sceGuSetCallback(int index, void (*callback)(int));
extern void sceGuSignal(int a0, int a1);

/**
  * Send raw float-command to the GE
  *
  * The argument is converted into a 24-bit float before transfer.
  *
  * @param cmd - Which command to send
  * @param argument - Argument to pass along
**/
extern void sceGuSendCommandf(int cmd, float argument);

/**
  * Send raw command to the GE
  *
  * Only the 24 lower bits of the argument is passed along.
  *
  * @param cmd - Which command to send
  * @param argument - Argument to pass along
**/
extern void sceGuSendCommandi(int cmd, int argument);

/**
  * Allocate memory on the current display list for temporary storage
  *
  * @param size - How much memory to allocate
  * @returns Memory-block ready for use
**/
extern void* sceGuGetMemory(int size);

/**
  * Start filling a new display-context
  *
  * Contexts available are:
  *   - GU_DIRECT - Rendering is performed as list is filled
  *   - GU_CALL - List is setup to be called from the main list
  *   - GU_SEND - List is buffered for a later call to sceGuSendList()
  *
  * The previous context-type is stored so that it can be restored at sceGuFinish().
  *
  * @param cid - Context Type
  * @param list - Pointer to display-list (16 byte aligned)
**/
extern void sceGuStart(int cid, void* list);
extern void sceGuStartJs(int cid);
/**
  * Finish current display list and go back to the parent context
  *
  * If the context is GU_DIRECT, the stall-address is updated so that the entire list will
  * execute. Otherwise, only the terminating action is written to the list, depending on
  * context-type.
  *
  * This also restores control back to whatever context that was active prior to this call.
  *
  * @returns Size of finished display list
**/
extern int sceGuFinish(void);

/**
  * Call previously generated display-list
  *
  * @param list - Display list to call
**/
extern void sceGuCallList(const void* list);

extern void sceGuCallMode(int mode);

/**
  * Check how large the current display-list is
  *
  * @returns The size of the current display list
**/
extern int sceGuCheckList(void);

/**
  * Send a list to the GE directly
  *
  * Available modes are:
  *   - GU_TAIL - Place list last in the queue, so it executes in-order
  *   - GU_HEAD - Place list first in queue so that it executes as soon as possible
  *
  * @param mode - Wether to place the list first or last in queue
  * @param list - List to send
  * @param context - Temporary storage for the GE context
**/
extern void sceGuSendList(int mode, const void* list, PspGeContext* context);

/**
  * Swap display and draw buffer
  *
  * @returns Pointer to the new drawbuffer
**/
extern void* sceGuSwapBuffers(void);

/**
  * Wait until display list has finished executing
  *
  * @par Example: Wait for the currently executing display list
  * @code
  * sceGuSync(0,0);
  * @endcode
  *
  * @param mode - Unknown meaning, pass 0 for now
  * @param a1 - Unknown meaning, pass 0 for now
  * @returns Unknown at this time
**/
extern int sceGuSync(int mode, int a1);

/**
  * Draw array of vertices forming primitives
  *
  * Available primitive-types are:
  *   - GU_POINTS - Single pixel points (1 vertex per primitive)
  *   - GU_LINES - Single pixel lines (2 vertices per primitive)
  *   - GU_LINE_STRIP - Single pixel line-strip (2 vertices for the first primitive, 1 for every following)
  *   - GU_TRIANGLES - Filled triangles (3 vertices per primitive)
  *   - GU_TRIANGLE_STRIP - Filled triangles-strip (3 vertices for the first primitive, 1 for every following)
  *   - GU_TRIANGLE_FAN - Filled triangle-fan (3 vertices for the first primitive, 1 for every following)
  *   - GU_SPRITES - Filled blocks (2 vertices per primitive)
  *
  * The vertex-type decides how the vertices align and what kind of information they contain.
  * The following flags are ORed together to compose the final vertex format:
  *   - GU_TEXTURE_8BIT - 8-bit texture coordinates
  *   - GU_TEXTURE_16BIT - 16-bit texture coordinates
  *   - GU_TEXTURE_32BITF - 32-bit texture coordinates (float)
  *
  *   - GU_COLOR_5650 - 16-bit color (R5G6B5A0)
  *   - GU_COLOR_5551 - 16-bit color (R5G5B5A1)
  *   - GU_COLOR_4444 - 16-bit color (R4G4B4A4)
  *   - GU_COLOR_8888 - 32-bit color (R8G8B8A8)
  *
  *   - GU_NORMAL_8BIT - 8-bit normals
  *   - GU_NORMAL_16BIT - 16-bit normals
  *   - GU_NORMAL_32BITF - 32-bit normals (float)
  *
  *   - GU_VERTEX_8BIT - 8-bit vertex position
  *   - GU_VERTEX_16BIT - 16-bit vertex position
  *   - GU_VERTEX_32BITF - 32-bit vertex position (float)
  *
  *   - GU_WEIGHT_8BIT - 8-bit weights
  *   - GU_WEIGHT_16BIT - 16-bit weights
  *   - GU_WEIGHT_32BITF - 32-bit weights (float)
  *
  *   - GU_INDEX_8BIT - 8-bit vertex index
  *   - GU_INDEX_16BIT - 16-bit vertex index
  *
  *   - GU_WEIGHTS(n) - Number of weights (1-8)
  *   - GU_VERTICES(n) - Number of vertices (1-8)
  *
  *   - GU_TRANSFORM_2D - Coordinate is passed directly to the rasterizer
  *   - GU_TRANSFORM_3D - Coordinate is transformed before passed to rasterizer
  *
  * NOTE: Every vertex must align to 32 bits, which means that you HAVE to pad if it does not add up!
  *
  * Vertex order:
  * [for vertices(1-8)]
  * [texture uv]
  * [weights (0-8)]
  * [color]
  * [normal]
  * [vertex]
  * [/for]
  *
  * @par Example: Render 400 triangles, with floating-point texture coordinates, and floating-point position, no indices
  * @code
  * sceGuDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_VERTEX_32BITF,400*3,0,vertices);
  * @endcode
  *
  * @param prim - What kind of primitives to render
  * @param vtype - Vertex type to process
  * @param count - How many vertices to process
  * @param indices - Optional pointer to an index-list
  * @param vertices - Pointer to a vertex-list
**/
extern void sceGuDrawArray(int prim, int vtype, int count, const void* indices, const void* vertices);

/**
  * Begin conditional rendering of object
  *
  * If no vertices passed into this function are inside the scissor region, it will skip rendering
  * the object. There can be up to 32 levels of conditional testing, and all levels HAVE to
  * be terminated by sceGuEndObject().
  *
  * @par Example: test a boundingbox against the frustum, and if visible, render object
  * @code
  * sceGuBeginObject(GU_VERTEX_32BITF,8,0,boundingBox);
  *   sceGuDrawArray(GU_TRIANGLES,GU_TEXTURE_32BITF|GU_VERTEX_32BITF,vertexCount,0,vertices);
  * sceGuEndObject();
  * @endcode
  *
  * @param vtype - Vertex type to process
  * @param count - Number of vertices to test
  * @param indices - Optional list to an index-list
  * @param vertices - Pointer to a vertex-list
**/
extern void sceGuBeginObject(int vtype, int count, const void* indices, const void* vertices);

/**
  * End conditional rendering of object
**/
extern void sceGuEndObject(void);

/**
  * Enable or disable GE state
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param state - Which state to change
  * @param status - Wether to enable or disable the state
**/
extern void sceGuSetStatus(int state, int status);

/**
  * Get if state is currently enabled or disabled
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param state - Which state to query about
  * @returns Wether state is enabled or not
**/
extern int sceGuGetStatus(int state);

/**
  * Set the status on all 22 available states
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param status - Bit-mask (0-21) containing the status of all 22 states
**/
extern void sceGuSetAllStatus(int status);

/**
  * Query status on all 22 available states
  *
  * Look at sceGuEnable() for a list of states
  *
  * @returns Status of all 22 states as a bitmask (0-21)
**/
extern int sceGuGetAllStatus(void);

/**
  * Enable GE state
  *
  * The currently available states are:
  *   - GU_ALPHA_TEST
  *   - GU_DEPTH_TEST
  *   - GU_SCISSOR_TEST
  *   - GU_BLEND
  *   - GU_CULL_FACE
  *   - GU_DITHER
  *   - GU_CLIP_PLANES
  *   - GU_TEXTURE_2D
  *   - GU_LIGHTING
  *   - GU_LIGHT0
  *   - GU_LIGHT1
  *   - GU_LIGHT2
  *   - GU_LIGHT3
  *   - GU_COLOR_LOGIC_OP
  *
  * @param state - Which state to enable
**/
extern void sceGuEnable(int state);

/**
  * Disable GE state
  *
  * Look at sceGuEnable() for a list of states
  *
  * @param state - Which state to disable
**/
extern void sceGuDisable(int state);

/**
  * Set light parameters
  *
  * Available light types are:
  *   - GU_DIRECTIONAL - Directional light
  *   - GU_POINTLIGHT - Single point of light
  *   - GU_SPOTLIGHT - Point-light with a cone
  *
  * Available light components are:
  *   - GU_AMBIENT_AND_DIFFUSE
  *   - GU_DIFFUSE_AND_SPECULAR
  *   - GU_UNKNOWN_LIGHT_COMPONENT
  *
  * @param light - Light index
  * @param type - Light type
  * @param components - Light components
  * @param position - Light position
**/
extern void sceGuLight(int light, int type, int components, const ScePspFVector3* position);

/**
  * Set light attenuation
  *
  * @param light - Light index
  * @param atten0 - Constant attenuation factor
  * @param atten1 - Linear attenuation factor
  * @param atten2 - Quadratic attenuation factor
**/
extern void sceGuLightAtt(int light, float atten0, float atten1, float atten2);

/**
  * Set light color
  *
  * Available light components are:
  *   - GU_AMBIENT
  *   - GU_DIFFUSE
  *   - GU_SPECULAR
  *   - GU_AMBIENT_AND_DIFFUSE
  *   - GU_DIFFUSE_AND_SPECULAR
  *
  * @param light - Light index
  * @param component - Which component to set
  * @param color - Which color to use
**/
extern void sceGuLightColor(int light, int component, unsigned int color);

extern void sceGuLightMode(int mode);

extern void sceGuLightSpot(int index, const ScePspFVector3* direction, float f12, float f13);

/**
  * Clear current drawbuffer
  *
  * Available clear-flags are (OR them together to get final clear-mode):
  *   - GU_COLOR_BUFFER_BIT - Clears the color-buffer
  *   - GU_STENCIL_BUFFER_BIT - Clears the stencil-buffer
  *   - GU_DEPTH_BUFFER_BIT - Clears the depth-buffer
  *
  * @param flags - Which part of the buffer to clear
**/
extern void sceGuClear(int flags);

/**
  * Set the current clear-color
  *
  * @param color - Color to clear with
**/
extern void sceGuClearColor(unsigned int color);

/**
  * Set the current clear-depth
  *
  * @param depth - Set which depth to clear with (0x0000-0xffff)
**/
extern void sceGuClearDepth(unsigned int depth);

/**
  * Set the current stencil clear value
  *
  * @param stencil - Set which stencil value to clear with (0-255)
  *
**/
extern void sceGuClearStencil(unsigned int stencil);

/**
  * Set mask for which bits of the pixels to write
  *
  * @param mask - Which bits to filter against writes
  *
**/
extern void sceGuPixelMask(unsigned int mask);

/**
  * Set current primitive color
  *
  * @param color - Which color to use (overriden by vertex-colors)
**/
extern void sceGuColor(unsigned int color);

/**
  * Set the color test function
  *
  * The color test is only performed while GU_COLOR_TEST is enabled.
  *
  * Available functions are:
  *   - GU_NEVER
  *   - GU_ALWAYS
  *   - GU_EQUAL
  *   - GU_NOTEQUAL
  *
  * @par Example: Reject any pixel that does not have 0 as the blue channel
  * @code
  * sceGuColorFunc(GU_EQUAL,0,0xff0000);
  * @endcode
  *
  * @param func - Color test function
  * @param color - Color to test against
  * @param mask - Mask ANDed against both source and destination when testing
**/
extern void sceGuColorFunc(int func, unsigned int color, unsigned int mask);

/**
  * Set which color components that the material will receive
  *
  * The components are ORed together from the following values:
  *   - GU_AMBIENT
  *   - GU_DIFFUSE
  *   - GU_SPECULAR
  *
  * @param components - Which components to receive
**/
extern void sceGuColorMaterial(int components);

/**
  * Set the alpha test parameters
  * 
  * Available comparison functions are:
  *   - GU_NEVER
  *   - GU_ALWAYS
  *   - GU_EQUAL
  *   - GU_NOTEQUAL
  *   - GU_LESS
  *   - GU_LEQUAL
  *   - GU_GREATER
  *   - GU_GEQUAL
  *
  * @param func - Specifies the alpha comparison function.
  * @param value - Specifies the reference value that incoming alpha values are compared to.
  * @param mask - Specifies the mask that both values are ANDed with before comparison.
**/
extern void sceGuAlphaFunc(int func, int value, int mask);

extern void sceGuAmbient(unsigned int color);
extern void sceGuAmbientColor(unsigned int color);

/**
  * Set the blending-mode
  *
  * Keys for the blending operations:
  *   - Cs - Source color
  *   - Cd - Destination color
  *   - Bs - Blend function for source fragment
  *   - Bd - Blend function for destination fragment
  *
  * Available blending-operations are:
  *   - GU_ADD - (Cs*Bs) + (Cd*Bd)
  *   - GU_SUBTRACT - (Cs*Bs) - (Cd*Bd)
  *   - GU_REVERSE_SUBTRACT - (Cd*Bd) - (Cs*Bs)
  *   - GU_MIN - Cs < Cd ? Cs : Cd
  *   - GU_MAX - Cs < Cd ? Cd : Cs
  *   - GU_ABS - |Cs-Cd|
  *
  * Available blending-functions are:
  *   - GU_SRC_COLOR
  *   - GU_ONE_MINUS_SRC_COLOR
  *   - GU_SRC_ALPHA
  *   - GU_ONE_MINUS_SRC_ALPHA
  *   - GU_DST_ALPHA
  *   - GU_ONE_MINUS_DST_ALPHA
  *   - GU_DST_COLOR
  *   - GU_ONE_MINUS_DST_COLOR
  *   - GU_FIX
  *
  * @param op - Blending Operation
  * @param src - Blending function for source operand
  * @param dest - Blending function for dest operand
  * @param srcfix - Fix value for GU_FIX (source operand)
  * @param destfix - Fix value for GU_FIX (dest operand)
**/
extern void sceGuBlendFunc(int op, int src, int dest, unsigned int srcfix, unsigned int destfix);

extern void sceGuMaterial(int mode, int color);

/**
  *
**/
extern void sceGuModelColor(unsigned int emissive, unsigned int ambient, unsigned int diffuse, unsigned int specular);

/**
  * Set stencil function and reference value for stencil testing
  *
  * Available functions are:
  *   - GU_NEVER
  *   - GU_ALWAYS
  *   - GU_EQUAL
  *   - GU_NOTEQUAL
  *   - GU_LESS
  *   - GU_LEQUAL
  *   - GU_GREATER
  *   - GU_GEQUAL
  *
  * @param func - Test function
  * @param ref - The reference value for the stencil test
  * @param mask - Mask that is ANDed with both the reference value and stored stencil value when the test is done
**/
extern void sceGuStencilFunc(int func, int ref, int mask);

/**
  * Set the stencil test actions
  *
  * Available actions are:
  *   - GU_KEEP - Keeps the current value
  *   - GU_ZERO - Sets the stencil buffer value to zero
  *   - GU_REPLACE - Sets the stencil buffer value to ref, as specified by sceGuStencilFunc()
  *   - GU_INCR - Increments the current stencil buffer value
  *   - GU_DECR - Decrease the current stencil buffer value
  *   - GU_INVERT - Bitwise invert the current stencil buffer value
  *
  * As stencil buffer shares memory with framebuffer alpha, resolution of the buffer
  * is directly in relation.
  *
  * @param fail - The action to take when the stencil test fails
  * @param zfail - The action to take when stencil test passes, but the depth test fails
  * @param zpass - The action to take when both stencil test and depth test passes
**/
extern void sceGuStencilOp(int fail, int zfail, int zpass);

/**
  * Set the specular power for the material
  *
  * @param power - Specular power
  *
**/
extern void sceGuSpecular(float power);

/**
  * Set the current face-order (for culling)
  *
  * This only has effect when culling is enabled (GU_CULL_FACE)
  *
  * Culling order can be:
  *   - GU_CW - Clockwise primitives are not culled
  *   - GU_CCW - Counter-clockwise are not culled
  *
  * @param order - Which order to use
**/
extern void sceGuFrontFace(int order);

/**
  * Set color logical operation
  *
  * Available operations are:
  *   - GU_CLEAR
  *   - GU_AND
  *   - GU_AND_REVERSE 
  *   - GU_COPY
  *   - GU_AND_INVERTED
  *   - GU_NOOP
  *   - GU_XOR
  *   - GU_OR
  *   - GU_NOR
  *   - GU_EQUIV
  *   - GU_INVERTED
  *   - GU_OR_REVERSE
  *   - GU_COPY_INVERTED
  *   - GU_OR_INVERTED
  *   - GU_NAND
  *   - GU_SET
  *
  * This operation only has effect if GU_COLOR_LOGIC_OP is enabled.
  *
  * @param op - Operation to execute
**/
extern void sceGuLogicalOp(int op);

/**
  * Set ordered pixel dither matrix
  *
  * This dither matrix is only applied if GU_DITHER is enabled.
  *
  * @param matrix - Dither matrix
**/
extern void sceGuSetDither(const ScePspIMatrix4* matrix);

/**
  * Set how primitives are shaded
  *
  * The available shading-methods are:
  *   - GU_FLAT - Primitives are flatshaded, the last vertex-color takes effet
  *   - GU_SMOOTH - Primtives are gouraud-shaded, all vertex-colors take effect
  *
  * @param mode - Which mode to use
**/
extern void sceGuShadeModel(int mode);

/**
  * Image transfer using the GE
  *
  * NOTE: Data must be aligned to 1 quad word (16 bytes)
  *
  * @par Example: Copy a fullscreen 32-bit image from RAM to VRAM
  * @code
  * sceGuCopyImage(GU_PSM_8888,0,0,480,272,512,pixels,0,0,512,(void*)(((unsigned int)framebuffer)+0x4000000));
  * @endcode
  *
  * @param psm - Pixel format for buffer
  * @param sx - Source X
  * @param sy - Source Y
  * @param width - Image width
  * @param height - Image height
  * @param srcw - Source buffer width (block aligned)
  * @param src - Source pointer
  * @param dx - Destination X
  * @param dy - Destination Y
  * @param destw - Destination buffer width (block aligned)
  * @param dest - Destination pointer
**/
extern void sceGuCopyImage(int psm, int sx, int sy, int width, int height, int srcw, void* src, int dx, int dy, int destw, void* dest);

/**
  * Specify the texture environment color
  *
  * This is used in the texture function when a constant color is needed.
  *
  * See sceGuTexFunc() for more information.
  *
  * @param color - Constant color (0x00BBGGRR)
**/
extern void sceGuTexEnvColor(unsigned int color);

/**
  * Set how the texture is filtered
  *
  * Available filters are:
  *   - GU_NEAREST
  *   - GU_LINEAR
  *   - GU_NEAREST_MIPMAP_NEAREST
  *   - GU_LINEAR_MIPMAP_NEAREST
  *   - GU_NEAREST_MIPMAP_LINEAR
  *   - GU_LINEAR_MIPMAP_LINEAR
  *
  * @param min - Minimizing filter
  * @param mag - Magnifying filter
**/
extern void sceGuTexFilter(int min, int mag);

/**
  * Flush texture page-cache
  *
  * Do this if you have copied/rendered into an area currently in the texture-cache
  *
**/
extern void sceGuTexFlush(void);

/**
  * Set how textures are applied
  *
  * Key for the apply-modes:
  *   - Cv - Color value result
  *   - Ct - Texture color
  *   - Cf - Fragment color
  *   - Cc - Constant color (specified by sceGuTexEnvColor())
  *
  * Available apply-modes are: (TFX)
  *   - GU_TFX_MODULATE - Cv=Ct*Cf TCC_RGB: Av=Af TCC_RGBA: Av=At*Af
  *   - GU_TFX_DECAL - TCC_RGB: Cv=Ct,Av=Af TCC_RGBA: Cv=Cf*(1-At)+Ct*At Av=Af
  *   - GU_TFX_BLEND - Cv=(Cf*(1-Ct))+(Cc*Ct) TCC_RGB: Av=Af TCC_RGBA: Av=At*Af
  *   - GU_TFX_REPLACE - Cv=Ct TCC_RGB: Av=Af TCC_RGBA: Av=At
  *   - GU_TFX_ADD - Cv=Cf+Ct TCC_RGB: Av=Af TCC_RGBA: Av=At*Af
  *
  * The fields TCC_RGB and TCC_RGBA specify components that differ between
  * the two different component modes.
  *
  *   - GU_TFX_MODULATE - The texture is multiplied with the current diffuse fragment
  *   - GU_TFX_REPLACE - The texture replaces the fragment
  *   - GU_TFX_ADD - The texture is added on-top of the diffuse fragment
  *   
  * Available component-modes are: (TCC)
  *   - GU_TCC_RGB - The texture alpha does not have any effect
  *   - GU_TCC_RGBA - The texture alpha is taken into account
  *
  * @param tfx - Which apply-mode to use
  * @param tcc - Which component-mode to use
**/
extern void sceGuTexFunc(int tfx, int tcc);

/**
  * Set current texturemap
  *
  * Textures may reside in main RAM, but it has a huge speed-penalty. Swizzle textures
  * to get maximum speed.
  *
  * NOTE: Data must be aligned to 1 quad word (16 bytes)
  *
  * @param mipmap - Mipmap level
  * @param width - Width of texture (must be a power of 2)
  * @param height - Height of texture (must be a power of 2)
  * @param tbw - Texture Buffer Width (block-aligned)
  * @param tbp - Texture buffer pointer (16 byte aligned)
**/
extern void sceGuTexImage(int mipmap, int width, int height, int tbw, const void* tbp);
extern void sceGuTexLevelMode(unsigned int a0, float f12);

/**
  * Set the texture-mapping mode
  *
  * Available modes are:
  *   - GU_TEXTURE_COORDS
  *   - GU_TEXTURE_MATRIX
  *   - GU_ENVIRONMENT_MAP
  *
  * @param mode - Which mode to use
  * @param a1 - Unknown
  * @param a2 - Unknown
**/
extern void sceGuTexMapMode(int mode, unsigned int a1, unsigned int a2);

/**
  * Set texture-mode parameters
  *
  * Available texture-formats are:
  *   - GU_PSM_5650 - Hicolor, 16-bit
  *   - GU_PSM_5551 - Hicolor, 16-bit
  *   - GU_PSM_4444 - Hicolor, 16-bit
  *   - GU_PSM_8888 - Truecolor, 32-bit
  *   - GU_PSM_T4 - Indexed, 4-bit (2 pixels per byte)
  *   - GU_PSM_T8 - Indexed, 8-bit
  *
  * @param tpsm - Which texture format to use
  * @param maxmips - Number of mipmaps to use (0-8)
  * @param a2 - Unknown, set to 0
  * @param swizzle - GU_TRUE(1) to swizzle texture-reads
**/
extern void sceGuTexMode(int tpsm, int maxmips, int a2, int swizzle);
extern void sceGuTexOffset(float u, float v);

/**
  * Set texture projection-map mode
  *
  * Available modes are:
  *   - GU_POSITION
  *   - GU_UV
  *   - GU_NORMALIZED_NORMAL
  *   - GU_NORMAL
  *
  * @param mode - Which mode to use
**/
extern void sceGuTexProjMapMode(int mode);

extern void sceGuTexScale(float u, float v);
extern void sceGuTexSlope(float slope);
extern void sceGuTexSync();

/**
  * Set if the texture should repeat or clamp
  *
  * Available modes are:
  *   - GU_REPEAT - The texture repeats after crossing the border
  *   - GU_CLAMP - Texture clamps at the border
  *
  * @param u - Wrap-mode for the U direction
  * @param v - Wrap-mode for the V direction
**/
extern void sceGuTexWrap(int u, int v);

/**
  * Upload CLUT (Color Lookup Table)
  *
  * NOTE: Data must be aligned to 1 quad word (16 bytes)
  *
  * @param num_blocks - How many blocks of 8 entries to upload (32*8 is 256 colors)
  * @param cbp - Pointer to palette (16 byte aligned)
**/
extern void sceGuClutLoad(int num_blocks, const void* cbp);

/**
  * Set current CLUT mode
  *
  * Available pixel formats for palettes are:
  *   - GU_PSM_5650
  *   - GU_PSM_5551
  *   - GU_PSM_4444
  *   - GU_PSM_8888
  *
  * @param cpsm - Which pixel format to use for the palette
  * @param a1 - Unknown, set to 0
  * @param a2 - Unknown, set to 0
  * @param a3 - Unknown, set to 0
**/
extern void sceGuClutMode(unsigned int cpsm, unsigned int a1, unsigned int a2, unsigned int a3);

/**
  * Set virtual coordinate offset
  *
  * The PSP has a virtual coordinate-space of 4096x4096, this controls where rendering is performed
  * 
  * @par Example: Center the virtual coordinate range
  * @code
  * sceGuOffset(2048-(480/2),2048-(480/2));
  * @endcode
  *
  * @param x - Offset (0-4095)
  * @param y - Offset (0-4095)
**/
extern void sceGuOffset(unsigned int x, unsigned int y);

/**
  * Set what to scissor within the current viewport
  *
  * Note that scissoring is only performed if the custom scissoring is enabled (GU_SCISSOR_TEST)
  *
  * @param x - Left of scissor region
  * @param y - Top of scissor region
  * @param w - Width of scissor region
  * @param h - Height of scissor region
**/
extern void sceGuScissor(int x, int y, int w, int h);

/**
  * Set current viewport
  *
  * @par Example: Setup a viewport of size (480,272) with origo at (2048,2048)
  * @code
  * sceGuViewport(2048,2048,480,272);
  * @endcode
  *
  * @param cx - Center for horizontal viewport
  * @param cy - Center for vertical viewport
  * @param width - Width of viewport
  * @param height - Height of viewport
**/
extern void sceGuViewport(int cx, int cy, int width, int height);

/* patches */
extern void sceGuDrawBezier(int vtype, int ucount, int vcount, const void* indices, const void* vertices);
extern void sceGuPatchDivide(unsigned int a0, unsigned int a1);
extern void sceGuPatchFrontFace(unsigned int a0);
extern void sceGuPatchPrim(unsigned int a0);
extern void sceGuDrawSpline(int vtype, int ucount, int vcount, int uedge, int vedge, const void* indices, const void* vertices);

/**
  * Set transform matrices
  *
  * Available matrices are:
  *   - GU_PROJECTION - View->Projection matrix
  *   - GU_VIEW - World->View matrix
  *   - GU_MODEL - Model->World matrix
  *   - GU_TEXTURE - Texture matrix
  *
  * @param type - Which matrix-type to set
  * @param matrix - Matrix to load
**/
extern void sceGuSetMatrix(int type, const ScePspFMatrix4* matrix);

/**
  * Specify skinning matrix entry
  *
  * To enable vertex skinning, pass GU_WEIGHTS(n), where n is between
  * 1-8, and pass available GU_WEIGHT_??? declaration. This will change
  * the amount of weights passed in the vertex araay, and by setting the skinning,
  * matrices, you will multiply each vertex every weight and vertex passed.
  *
  * Please see sceGuDrawArray() for vertex format information.
  *
  * @param index - Skinning matrix index (0-7)
  * @param matrix - Matrix to set
**/
extern void sceGuBoneMatrix(unsigned int index, const ScePspFMatrix4* matrix);

/**
  * Specify morph weight entry
  *
  * To enable vertex morphing, pass GU_VERTICES(n), where n is between
  * 1-8. This will change the amount of vertices passed in the vertex array,
  * and by setting the morph weights for every vertex entry in the array,
  * you can blend between them.
  *
  * Please see sceGuDrawArray() for vertex format information.
  *
  * @param index - Morph weight index (0-7)
  * @param weight - Weight to set
**/
extern void sceGuMorphWeight(int index, float weight);

extern void sceGuSpriteMode(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);

extern void sceGuDrawArrayN(int primitive_type, int vertex_type, int count, int a3, const void* indices, const void* vertices);

/*@}*/

#if defined(__cplusplus)
};
#endif

#endif
