#pragma once

#include "pch.hpp"

#include "Calculations.hpp"

struct Fraction 
{
  const long WholeNumber;
  const long Numerator;
  const long Denominator;

  constexpr Fraction(long whole, long numerator, long denominator) :
    WholeNumber(whole),
    Numerator(numerator),
    Denominator(denominator)
  {};

  constexpr const double ToDouble() const
  {
    return Numerator > 0 && Denominator > 0
      ? WholeNumber + (static_cast<const double>(Numerator) / Denominator)
      : WholeNumber;
  }

  const bool operator < (const Fraction& rhs) const
  {
    if (WholeNumber < rhs.WholeNumber)
    {
      return true;
    }

    auto lhsFract = Numerator > 0 && Denominator > 0;
    auto rhsFract = rhs.Numerator > 0 && rhs.Denominator > 0;

    auto lhsFp = 0.0;
    auto rhsFp = 0.0;

    if (lhsFract)
    {
      lhsFp = (static_cast<const double>(Numerator) / Denominator);
    }
    else
    {
      return false;
    }

    if (rhsFract)
    {
      rhsFp = (static_cast<const double>(rhs.Numerator) / rhs.Denominator);
    }
    else
    {
      return true;
    }

    if (DoubleMath::IsSimilar(lhsFp, rhsFp, std::numeric_limits<double>::epsilon()))
    {
      return false;
    }

    return lhsFp < rhsFp;
  }

  const bool operator > (const Fraction& rhs) const
  {
    if (WholeNumber > rhs.WholeNumber)
    {
      return true;
    }

    auto lhsFract = Numerator > 0 && Denominator > 0;
    auto rhsFract = rhs.Numerator > 0 && rhs.Denominator > 0;

    auto lhsFp = 0.0;
    auto rhsFp = 0.0;

    if (lhsFract)
    {
      lhsFp = (static_cast<const double>(Numerator) / Denominator);
    }
    else
    {
      return false;
    }

    if (rhsFract)
    {
      rhsFp = (static_cast<const double>(rhs.Numerator) / rhs.Denominator);
    }
    else
    {
      return true;
    }

    if (DoubleMath::IsSimilar(lhsFp, rhsFp, std::numeric_limits<double>::epsilon()))
    {
      return false;
    }

    return lhsFp > rhsFp;
  }

  const bool operator <= (const Fraction& rhs) const
  {
    return !operator> (rhs);
  }

  const bool operator >= (const Fraction& rhs) const
  {
    return !operator< (rhs);
  }

  const bool operator == (const Fraction& rhs) const
  {
    auto lhsFract = Numerator > 0 && Denominator > 0;
    auto rhsFract = rhs.Numerator > 0 && rhs.Denominator > 0;

    auto lhsFp = 0.0;
    auto rhsFp = 0.0;

    if (lhsFract)
    {
      lhsFp = (static_cast<const double>(Numerator) / Denominator);
    }

    if (rhsFract)
    {
      rhsFp = (static_cast<const double>(rhs.Numerator) / rhs.Denominator);
    }

    return !lhsFract && !rhsFract || DoubleMath::IsSimilar(lhsFp, rhsFp, std::numeric_limits<double>::epsilon());
  }

  const bool operator != (const Fraction& rhs) const
  {
    return !operator==(rhs);
  }
};

template<size_t W,
  size_t N,
  size_t D,
  class A>
struct TMP_Fraction : A
{
  static const size_t Whole = W;
  static const size_t Num = N;
  static const size_t Den = D;

  constexpr TMP_Fraction() : A(W, N, D) {};
};

template<size_t W,
  size_t N,
  size_t D,
  size_t FO,
  class A>
  struct TMP_Fraction_Ext : TMP_Fraction<W, N, D, A>
{
  static const size_t AssociatedOctaves = FO;
};

template <int X, int Y>   struct MCD {
  static const long result = MCD<Y, X % Y>::result;
};

template <int X> struct MCD<X, 0> {
  static const long result = X;
};

template <class F> struct Simpl {
  static const long mcd = MCD<F::Num, F::Den>::result;
  typedef typename TMP_Fraction<F::Whole, F::Num / mcd, F::Den / mcd > result;
};
