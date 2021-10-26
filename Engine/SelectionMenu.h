#pragma once

#include "RectI.h"
#include "SpriteCode.h"
#include "Mouse.h"
#include "Sound.h"

class SelectionMenu
{
public:
	enum class Size
	{
		Small,
		Medium,
		Large,
		Count,
		Invalid
	};
private:
	class Entry
	{
	public:
		Entry() = default;
		Entry(Size s, const Vec2i& pos)
			:
			s(s),
			rect(RectI::FromCenter(pos, SpriteCode::sizeselWidth / 2, SpriteCode::sizeselHeight / 2))
		{}
		void Draw(Graphics& gfx) const
		{
			if (highlighted)
			{
				gfx.DrawRectWithRectI(rect.GetExpand(highlightThickness), highlightColor);
			}
			gfx.DrawRectWithRectI(rect, Colors::Black);
			DrawSizeText(s, { rect.left + 120,rect.top + 28}, gfx);
		}
		bool IsHit(const Vec2i& pt) const
		{
			return rect.IsInside(pt);
		}
		void ResetHighlight()
		{
			highlighted = false;
		}
		void SetHighlight()
		{
			highlighted = true;
		}
		bool IsHighlighted() const
		{
			return highlighted;
		}
		Size GetSize() const
		{
			return s;
		}
	private:
		static void DrawSizeText(Size s, const Vec2i& pos, Graphics& gfx)
		{
			switch (s)
			{
			case Size::Small:
				SpriteCode::DrawSmall(pos, gfx);
				break;
			case Size::Medium:
				SpriteCode::DrawMedium(pos, gfx);
				break;
			case Size::Large:
				SpriteCode::DrawLarge(pos, gfx);
				break;
			}
		}
	private:
		static constexpr int highlightThickness = 6;
		static constexpr Color highlightColor = Colors::Yellow;
		bool highlighted = false;
		Size s;
		RectI rect;
	};
public:
	SelectionMenu(const Vec2i& pos)
	{
		auto center = pos;
		for (int i = 0; i < int(Size::Count); i++)
		{
			entries[i] = { Size(i),center };
			center.y += verticalSpacing;
		}
	}
	// returns Size::Something when an entry is clicked, otherwise returns Size::Invalid
	Size ProcessMouse(const Mouse::Event& e)
	{
		switch (e.GetType())
		{
		case Mouse::Event::Type::Move:
			for (auto& n : entries)
			{
				if (n.IsHit(e.GetPos()))
				{
					// need to test here to prevent sfx from firing
					// on every mouse move event
					if (!n.IsHighlighted())
					{
						ResetHighlights();
						n.SetHighlight();
						hover.Play();
					}
					// immediately exit if found a hit
					// (if we don't, highlight will be reset below)
					return Size::Invalid;
				}
			}
			// if no entry was hit, reset all highlights
			ResetHighlights();
			break;
		case Mouse::Event::Type::LPress:
			for (auto& n : entries)
			{
				if (n.IsHit(e.GetPos()))
				{
					return n.GetSize();
				}
			}
			break;
		}
		return Size::Invalid;
	}
	void Draw(Graphics& gfx) const
	{
		for (const auto& n : entries)
		{
			n.Draw(gfx);
		}
	}
private:
	void ResetHighlights()
	{
		for (auto& n : entries)
		{
			n.ResetHighlight();
		}
	}
private:
	static constexpr int verticalSpacing = SpriteCode::sizeselHeight * 2;
	Sound hover = { L"Sounds\\menu_boop.wav" };
	Entry entries[int(Size::Count)];
};