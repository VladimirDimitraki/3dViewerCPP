#include <gtest/gtest.h>

#include <iostream>

#include "../Controller/controller.h"

class ViewerTest : public ::testing::Test {
 protected:
  s21::Model model_;
  s21::Controller controller_;
  static constexpr double kEpsilon_ = 1e-6;

  void SetUp() override { controller_ = s21::Controller(&model_); }
};

TEST_F(ViewerTest, CorrectCube) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}
TEST_F(ViewerTest, CorrectCar) {
  std::string file_path = "../src/tests/obj/correct/car.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, CorrectNegativeCube) {
  std::string file_path = "../src/tests/obj/correct/cube_neg.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, IncorrectFileName) {
  std::string file_path = "../src/tests/obj/correct/abrakadabra.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_FALSE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, IncorrectFileExtention) {
  std::string file_path = "../src/tests/obj/correct/cube.org";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_FALSE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, IncorrectFilePath) {
  std::string file_path = "../src/tests/obj/cor/cube.org";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_FALSE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, EmptyFilePath) {
  std::string file_path;
  controller_.SetCentre(&controller_.GetData());

  EXPECT_FALSE(model_.ProccessingObjFile(file_path));
}

/// All incorrect files

TEST_F(ViewerTest, alot_coordinates_in_vertex) {
  std::string file_path =
      "../src/tests/obj/incorrect/alot_coordinates_in_vertex.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, dot_error) {
  std::string file_path = "../src/tests/obj/incorrect/dot_error.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, facet_that_less_than_1) {
  std::string file_path =
      "../src/tests/obj/incorrect/facet_that_less_than_1.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, facet_that_not_exist) {
  std::string file_path = "../src/tests/obj/incorrect/facet_that_not_exist.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, first_minus) {
  std::string file_path = "../src/tests/obj/incorrect/first_minus.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, incorrect_notation) {
  std::string file_path = "../src/tests/obj/incorrect/incorrect_notation.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, incorrect_number) {
  std::string file_path = "../src/tests/obj/incorrect/incorrect_number.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, invalid_pretoken) {
  std::string file_path = "../src/tests/obj/incorrect/invalid_pretoken.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, invalid_token) {
  std::string file_path = "../src/tests/obj/incorrect/invalid_token.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, more_than_1_dot_in_number) {
  std::string file_path =
      "../src/tests/obj/incorrect/more_than_1_dot_in_number.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, stash) {
  std::string file_path = "../src/tests/obj/incorrect/stash.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, stash_in_line) {
  std::string file_path = "../src/tests/obj/incorrect/stash_in_line.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, test_with_russian_symb) {
  std::string file_path =
      "../src/tests/obj/incorrect/test_with_russian_symb.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, tsar_test) {
  std::string file_path = "../src/tests/obj/incorrect/tsar_test.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, vertex_less_than_3) {
  std::string file_path = "../src/tests/obj/incorrect/vertex_less_than_3.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

TEST_F(ViewerTest, zero_vertex) {
  std::string file_path = "../src/tests/obj/incorrect/zero_vertex.obj";
  controller_.SetCentre(&controller_.GetData());

  EXPECT_TRUE(model_.ProccessingObjFile(file_path));
}

// TEST AFFINE

TEST_F(ViewerTest, MovePlusX) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";

  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     3);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].x + 3, model_after[i].x);
  }
}

TEST_F(ViewerTest, MoveMinusX) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";

  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -3);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].x - 3, model_after[i].x);
  }
}

TEST_F(ViewerTest, MovePlusY) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     3);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].y + 3, model_after[i].y);
  }
}

TEST_F(ViewerTest, MoveMinusY) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     -3);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].y - 3, model_after[i].y);
  }
}

TEST_F(ViewerTest, MovePlusZ) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     3);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].z + 3, model_after[i].z);
  }
}

TEST_F(ViewerTest, MoveMinusZ) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     -3);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_EQ(model_before[i].z - 3, model_after[i].z);
  }
}

TEST_F(ViewerTest, RotateX) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     180);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, -model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, -model_after[i].z, kEpsilon_);
  }
}

TEST_F(ViewerTest, RotateY) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     180);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, -model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, -model_after[i].z, kEpsilon_);
  }
}

TEST_F(ViewerTest, RotateZ) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     180);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, -model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, -model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(ViewerTest, SummaryXYZMirrorRotateTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     30);
  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     30);
  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     30);

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     -30);
  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     -30);
  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -30);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(ViewerTest, SummaryXRotateTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     30);

  controller_.Affine(s21::Strategy::SelectionStrategy::kRotate,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -30);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(ViewerTest, PlusSizeTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kDistance,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     1.1);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x * 1.1, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y * 1.1, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z * 1.1, model_after[i].z, kEpsilon_);
  }
}

TEST_F(ViewerTest, MinusSizeTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  model_.ProccessingObjFile(file_path);

  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kDistance,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     0.9);

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x * 0.9, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y * 0.9, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z * 0.9, model_after[i].z, kEpsilon_);
  }
}

TEST_F(ViewerTest, SetCenterTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  controller_.ParseFile(file_path);

  controller_.SetCentre(&controller_.GetData());
  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     20);
  controller_.SetCentre(&controller_.GetData());

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(ViewerTest, SetCenterAfterMovingZYTest) {
  std::string file_path = "../src/tests/obj/correct/cube.obj";
  controller_.ParseFile(file_path);

  controller_.SetCentre(&controller_.GetData());
  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     -10);
  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -10);
  controller_.SetCentre(&controller_.GetData());

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(ViewerTest, SetCenterAfterMovingTest) {
  std::string file_path = "../src/tests/obj/correct/bison_pose.obj";
  controller_.ParseFile(file_path);

  controller_.SetCentre(&controller_.GetData());
  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     -10);
  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -10);
  controller_.SetCentre(&controller_.GetData());

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}

TEST_F(ViewerTest, SetCenterAfterZMovingTest) {
  std::string file_path = "../src/tests/obj/correct/katana.obj";
  controller_.ParseFile(file_path);

  controller_.SetCentre(&controller_.GetData());
  const auto model_before = controller_.GetData().GetCoordinateVertex();

  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kX, &controller_.GetData(),
                     -10);
  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kY, &controller_.GetData(),
                     -10);
  controller_.Affine(s21::Strategy::SelectionStrategy::kMove,
                     s21::Strategy::TypeCoordinate::kZ, &controller_.GetData(),
                     10);
  controller_.SetCentre(&controller_.GetData());

  const auto model_after = controller_.GetData().GetCoordinateVertex();

  for (size_t i = 0; i < model_before.size(); i++) {
    EXPECT_NEAR(model_before[i].x, model_after[i].x, kEpsilon_);
    EXPECT_NEAR(model_before[i].y, model_after[i].y, kEpsilon_);
    EXPECT_NEAR(model_before[i].z, model_after[i].z, kEpsilon_);
  }
}
