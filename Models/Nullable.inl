#include <stdexcept>

template <typename T>
inline Nullable<T>::Nullable()
	: hasValue(false)
{
}

template <typename T>
inline Nullable<T>::Nullable(T value)
	: value(value), hasValue(true)
{
}

template <typename T>
inline Nullable<T>::Nullable(std::nullptr_t)
	: hasValue(false)
{
}

template <typename T>
inline Nullable<T>& Nullable<T>::operator=(T value)
{
	this->value = value;
	hasValue = true;
	return *this;
}

template <typename T>
inline Nullable<T>& Nullable<T>::operator=(std::nullptr_t)
{
	hasValue = false;
	return *this;
}

template <typename T>
inline bool Nullable<T>::HasValue() const
{
	return hasValue;
}

template <typename T>
inline T Nullable<T>::GetValue() const
{
	if (!hasValue)
		throw std::runtime_error("Null value access.");
	return value;
}

template <typename T>
inline T Nullable<T>::GetValueOrDefault(T defaultValue) const
{
	return hasValue ? value : defaultValue;
}

template <typename T>
inline void Nullable<T>::SetValue(T value)
{
	this->value = value;
	hasValue = true;
}

template <typename T>
inline void Nullable<T>::SetValue(std::nullptr_t)
{
	hasValue = false;
}

template <typename T>
inline bool Nullable<T>::operator==(std::nullptr_t) const
{
	return !hasValue;
}

template <typename T>
inline bool Nullable<T>::operator!=(std::nullptr_t) const
{
	return hasValue;
}

