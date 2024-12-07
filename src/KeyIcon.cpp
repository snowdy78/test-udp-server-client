#include "KeyIcon.hpp"
#include "Font.hpp"
#include "components/FileLoader.hpp"


std::map<sf::Keyboard::Key, char> KeyIcon::key_map = {
	{ sf::Keyboard::A,		   'A'  },
	 { sf::Keyboard::B,			'B'	},
	{ sf::Keyboard::C,		   'C'  },
	{ sf::Keyboard::D,		   'D'  },
	 { sf::Keyboard::E,			'E'	},
	{ sf::Keyboard::F,		   'F'  },
	{ sf::Keyboard::G,		   'G'  },
	 { sf::Keyboard::H,			'H'	},
	{ sf::Keyboard::I,		   'I'  },
	{ sf::Keyboard::J,		   'J'  },
	 { sf::Keyboard::K,			'K'	},
	{ sf::Keyboard::L,		   'L'  },
	{ sf::Keyboard::M,		   'M'  },
	 { sf::Keyboard::N,			'N'	},
	{ sf::Keyboard::O,		   'O'  },
	{ sf::Keyboard::P,		   'P'  },
	 { sf::Keyboard::Q,			'Q'	},
	{ sf::Keyboard::R,		   'R'  },
	{ sf::Keyboard::S,		   'S'  },
	 { sf::Keyboard::T,			'T'	},
	{ sf::Keyboard::U,		   'U'  },
	{ sf::Keyboard::V,		   'V'  },
	 { sf::Keyboard::W,			'W'	},
	{ sf::Keyboard::X,		   'X'  },
	{ sf::Keyboard::Y,		   'Y'  },
	 { sf::Keyboard::Z,			'Z'	},
	{ sf::Keyboard::Num0,		  '0'  },
	{ sf::Keyboard::Num1,		  '1'  },
	 { sf::Keyboard::Num2,	   '2'  },
	{ sf::Keyboard::Num3,		  '3'  },
	{ sf::Keyboard::Num4,		  '4'  },
	 { sf::Keyboard::Num5,	   '5'  },
	{ sf::Keyboard::Num6,		  '6'  },
	{ sf::Keyboard::Num7,		  '7'  },
	 { sf::Keyboard::Num8,	   '8'  },
	{ sf::Keyboard::Num9,		  '9'  },
	{ sf::Keyboard::LBracket,	  '['  },
	 { sf::Keyboard::RBracket,   ']'  },
	{ sf::Keyboard::SemiColon,  ';'  },
	{ sf::Keyboard::Comma,	   ','  },
	 { sf::Keyboard::Period,	 '.'	 },
	{ sf::Keyboard::Apostrophe, '\'' },
	{ sf::Keyboard::Slash,	   '?'  },
	 { sf::Keyboard::Backslash,	'\\' },
	{ sf::Keyboard::Grave,	   '`'  },
	{ sf::Keyboard::Equal,	   '='  },
	 { sf::Keyboard::Subtract,   '-'  },
	{ sf::Keyboard::Add,		 '+'	 },
	{ sf::Keyboard::Multiply,	  '*'  },
	 { sf::Keyboard::Divide,	 '/'	 },
	{ sf::Keyboard::Hyphen,		'_'	}
};

sf::Color KeyIcon::color{ 68, 0, 255 };

const sf::Texture *const &KeyIcon::key_texture = FileLoader::Instance().addTextureToUpload("img/icons/0key-icon.png");

KeyIcon::KeyIcon(sf::Keyboard::Key key)
	: key_text(nullptr)
{
	if (key_map.find(key) != key_map.end())
	{
		key_text = new sf::Text(sf::String(key_map[key]), *Font::Jersey10);
        sprite.setTexture(*key_texture);
    }
}
KeyIcon::KeyIcon(const KeyIcon &other)
	: sprite(other.sprite),
	  key(other.key)
{
	key_text = other.key_text ? new sf::Text(*other.key_text) : nullptr;
}
KeyIcon::KeyIcon(KeyIcon &&other)
	: sprite(std::move(other.sprite)),
	  key(std::move(other.key))
{
	key_text = other.key_text ? new sf::Text(*other.key_text) : nullptr;
	delete other.key_text;
	other.key_text = nullptr;
}
KeyIcon::~KeyIcon()
{
	delete key_text;
}

KeyIcon &KeyIcon::operator=(const KeyIcon &other)
{
	if (this != &other)
	{
		sprite = other.sprite;
		key	   = other.key;
		delete key_text;
		key_text = other.key_text ? new sf::Text(*other.key_text) : nullptr;
	}
	return *this;
}
KeyIcon &KeyIcon::operator=(KeyIcon &&other) noexcept
{
	if (this != &other)
	{
		sprite = std::move(other.sprite);
		key	   = std::move(other.key);
		delete key_text;
		key_text = other.key_text;
		delete other.key_text;
		other.key_text = nullptr;
	}
	return *this;
}
bool KeyIcon::isIntersected(const rn::Vec2f &point) const
{
	return sprite.getGlobalBounds().contains(point);
}
void KeyIcon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
	if (key_text)
		target.draw(*key_text, states);
}
