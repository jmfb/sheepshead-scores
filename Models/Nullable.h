#pragma once
#include <cstddef>

template <typename T>
class Nullable
{
public:
	Nullable();
	Nullable(T value);
	Nullable(std::nullptr_t);
	Nullable(const Nullable<T>& rhs) = default;
	~Nullable() = default;
	
	Nullable<T>& operator=(const Nullable<T>& rhs) = default;
	Nullable<T>& operator=(T value);
	Nullable<T>& operator=(std::nullptr_t);
	
	bool HasValue() const;
	T GetValue() const;
	T GetValueOrDefault(T defaultValue = T()) const;
	void SetValue(T value);
	void SetValue(std::nullptr_t);

	bool operator==(std::nullptr_t) const;
	bool operator!=(std::nullptr_t) const;

private:
	T value;
	bool hasValue;
};

#include "Nullable.inl"

