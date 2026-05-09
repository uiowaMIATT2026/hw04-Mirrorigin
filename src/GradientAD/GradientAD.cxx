#include "GradientADCLP.h"
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkGradientAnisotropicDiffusionImageFilter.h"

int main(int argc, char * argv[])
{
  PARSE_ARGS;

  using PixelType = double;
  constexpr unsigned int Dimension = 3;
  using ImageType = itk::Image<PixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<ImageType>;
  using WriterType = itk::ImageFileWriter<ImageType>;
  using FilterType = itk::GradientAnisotropicDiffusionImageFilter<ImageType, ImageType>;

  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();
  FilterType::Pointer filter = FilterType::New();

  reader->SetFileName(inputVolume);
  writer->SetFileName(outputVolume);

  filter->SetInput(reader->GetOutput());
  filter->SetConductanceParameter(conductance);
  filter->SetTimeStep(timeStep);
  filter->SetNumberOfIterations(iterations);

  writer->SetInput(filter->GetOutput());

  try {
    writer->Update();
  }
  catch (itk::ExceptionObject & err)
  {
    std::cerr << "Exception: " << err << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}