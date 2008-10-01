
/*
 *
 *  ______             ___    ___      
 * /\__  _\           /\_ \  /\_ \     
 * \/_/\ \/ _ __   ___\//\ \ \//\ \    
 *    \ \ \/\`'__\/ __`\\ \ \  \ \ \   
 *     \ \ \ \ \//\ \L\ \\_\ \_ \_\ \_ 
 *      \ \_\ \_\\ \____//\____\/\____\
 *       \/_/\/_/ \/___/ \/____/\/____/
 *
 * Copyright (c) 2008, JarinSoft
 * All rights reserved.
 *
 * Vinicius Jarina (viniciusjarina@gmail.com)
 *
 * Visit: http://troll2d.googlecode.com
 *
 * Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *      * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the JarinSoft nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY JarinSoft ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL JARINSOFT BE LIABLE FOR ANY
 *   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __TROLL_DRAW_FLAGS_H__
#define __TROLL_DRAW_FLAGS_H__

namespace Troll
{
	class DrawFlags
	{
	public:
		enum EnumDrawFlags
		{
			none		   = 0x00,
			verticalFlip   = 0x01,
			horizontalFlip = 0x02,
			noAntiAlias    = 0x04,
		};

		explicit DrawFlags(int flags):
		m_flags((EnumDrawFlags)flags)
		{
		}

		DrawFlags(EnumDrawFlags flag):
		m_flags(flag)
		{
		}

		DrawFlags& operator = (EnumDrawFlags flag)
		{
			m_flags = flag;
			return *this;
		}

		inline void SetFlag(EnumDrawFlags flag)
		{
			m_flags = (EnumDrawFlags)((int)m_flags | (int)flag);
		}

		inline void UnsetFlag(EnumDrawFlags flag)
		{
			m_flags = (EnumDrawFlags)(((int)m_flags) & (~((int)flag)));
		}

		inline void ToggleFlag(EnumDrawFlags flag)
		{
			if(HasFlag(flag))
				UnsetFlag(flag);
			else
				SetFlag(flag);			
		}

		friend inline DrawFlags operator | (EnumDrawFlags flag,DrawFlags flag2);
		
		inline DrawFlags operator | (DrawFlags flag2) const
		{
			return (DrawFlags((int)m_flags|(int)flag2.m_flags));
		}

		inline DrawFlags operator | (EnumDrawFlags flag2) const
		{
			return (DrawFlags((int)m_flags|(int)flag2));
		}

		inline bool HasFlag(EnumDrawFlags flag) const
		{
			return ((int)m_flags & (int)flag) != 0;
		}

		friend inline int operator & (EnumDrawFlags flag,DrawFlags flag2);

	
		inline int operator & (EnumDrawFlags flag) const
		{
			return ((int)m_flags & (int)flag);
		}
		
	private:

		EnumDrawFlags m_flags;
	};

	inline DrawFlags operator | (DrawFlags::EnumDrawFlags flag,DrawFlags::EnumDrawFlags flag2)
	{
		return DrawFlags((int)flag2 | (int)flag);
	}

	inline DrawFlags operator | (DrawFlags::EnumDrawFlags flag,DrawFlags flag2)
	{
		return DrawFlags(flag2.m_flags | flag);
	}	
}

#endif // __TROLL_DRAW_FLAGS_H__