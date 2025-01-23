#include <gtkmm.h>
#include <iostream>

class WelcomeWizard : public Gtk::Window {
public:
  WelcomeWizard() {
    set_title("Welcome to LearnixOS");
    set_default_size(800, 600);

    m_box.set_orientation(Gtk::Orientation::VERTICAL);
    m_box.set_spacing(20);
    m_box.set_margin(20);

    m_content_box.set_orientation(Gtk::Orientation::HORIZONTAL);
    m_content_box.set_spacing(20);
    m_content_box.set_margin(10);

    m_text_box.set_orientation(Gtk::Orientation::VERTICAL);
    m_text_box.set_spacing(10);

    try {
      m_image.set("./logo.png");
      m_image.set_size_request(200, 200);
    } catch (const Glib::Error &ex) {
      std::cerr << "Error loading image: " << ex.what() << std::endl;
    }

    m_welcome_label.set_markup(
        "<span size='xx-large'>Welcome to LearnixOS!</span>");
    m_description.set_text("Thank you for choosing LearnixOS - a "
                           "learning-focused Linux distribution.\n"
                           "This wizard will help you get started with your "
                           "new operating system.");
    m_description.set_wrap(true);

    m_progress.set_fraction(0.0);

    m_next_button.set_label("Next >");
    m_next_button.signal_clicked().connect(
        sigc::mem_fun(*this, &WelcomeWizard::on_next_clicked));

    m_text_box.append(m_welcome_label);
    m_text_box.append(m_description);

    m_content_box.append(m_image);
    m_content_box.append(m_text_box);

    auto spacer = Gtk::make_managed<Gtk::Box>();
    spacer->set_vexpand(true);

    m_box.append(m_content_box);
    m_box.append(*spacer);
    m_box.append(m_progress);
    m_box.append(m_next_button);

    set_child(m_box);
  }

protected:
  void on_next_clicked() {
    if (m_current_page < 3) {
      m_current_page++;
      update_page();
    } else {
      hide();
    }
  }

  void update_page() {
    m_progress.set_fraction(m_current_page / 3.0);

    switch (m_current_page) {
    case 1:
      try {
        m_image.set("./logo.png");
      } catch (const Glib::Error &ex) {
        std::cerr << "Error loading image: " << ex.what() << std::endl;
      }
      m_description.set_text(
          "LearnixOS is designed to help you learn source-based Linux from the "
          "ground up.\n"
          "You'll discover how source based distros works while using it!");
      break;
    case 2:
      try {
        m_image.set("./logo.png");
      } catch (const Glib::Error &ex) {
        std::cerr << "Error loading image: " << ex.what() << std::endl;
      }
      m_description.set_text(
          "The system comes with custom tools and documentation.\n"
          "Check the Help menu to get started with tutorials.");
      break;
    case 3:
      try {
        m_image.set("./logo.png");
      } catch (const Glib::Error &ex) {
        std::cerr << "Error loading image: " << ex.what() << std::endl;
      }
      m_description.set_text(
          "You're all set! Click Next to begin using LearnixOS.");
      m_next_button.set_label("Finish");
      break;
    }
  }

private:
  Gtk::Box m_box;
  Gtk::Box m_content_box;
  Gtk::Box m_text_box;
  Gtk::Label m_welcome_label;
  Gtk::Label m_description;
  Gtk::Image m_image;
  Gtk::ProgressBar m_progress;
  Gtk::Button m_next_button;
  int m_current_page = 0;
};

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create("org.learnixos.welcome");

  return app->make_window_and_run<WelcomeWizard>(argc, argv);
}
