#ifndef DEFENSE_H
#define DEFENSE_H
enum class Defense {
	NONE,
	SLASH,
	PIERCE,
	BLUNT,
	CHOP,
	MAGIC,
	FIRE,
	FROST,
	SHOCK,
	WIND,
	POISON,
	BLEED,
	SLEEP,
	DARK,
	HOLY
};
namespace std {
	template <>
	struct hash<Defense> {
		std::size_t operator()(const Defense& d) const noexcept {
			return std::hash<int>()(static_cast<int>(d));
		}
	};
}

#endif // !DEFENSE_H
