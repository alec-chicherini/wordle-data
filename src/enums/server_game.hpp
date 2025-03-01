#pragma once

enum class LoginStatus {
  kNone = 0,
  kUserNameEmpty,
  kPasswordEmpty,
  kUnauthorized,
  kLoginIsOk,
  kRequestInProgress,
  kServerError
};

enum class RegistrationStatus {
  kNone = 0,
  kUserNameEmpty,
  kPasswordEmpty,
  kPasswordConfirmEmpty,
  kPasswordMismatch,
  kUserNameDuplicate,
  kRegistrationIsOk,
  kRequestInProgress,
  kBadEmailAddress,
  kServerError
};

enum class CheckTheRowResult {
  kNone = 0,
  kWordDoNotExists,
  kWordExists,
  kWordIsAnswer,
  kServerError
};

enum class TheCharColor { kNone, kGreen, kYellow };