#ifndef MainWindow_H
#define MainWindow_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMimeData>
#include "gui/customwidgets/overlaycontainerwidget.h"
#include "gui/viewers/viewerwidget.h"
#include "gui/overlays/controlsoverlay.h"
#include "gui/overlays/infooverlayproxy.h"
#include "gui/overlays/floatingmessageproxy.h"
#include "gui/overlays/saveconfirmoverlay.h"
#include "gui/panels/mainpanel/thumbnailstrip.h"
#include "gui/panels/mainpanel/mainpanel.h"
#include "gui/panels/sidepanel/sidepanel.h"
#include "gui/panels/croppanel/croppanel.h"
#include "gui/overlays/cropoverlay.h"
#include "gui/overlays/copyoverlay.h"
#include "gui/overlays/changelogwindow.h"
#include "gui/overlays/imageinfooverlayproxywrapper.h"
#include "gui/overlays/renameoverlay.h"
#include "gui/dialogs/resizedialog.h"
#include "gui/centralwidget.h"
#include "components/actionmanager/actionmanager.h"
#include "settings.h"
#include "gui/dialogs/settingsdialog.h"
#include "gui/viewers/documentwidget.h"
#include "gui/folderview/folderviewproxy.h"
#include "gui/panels/infobar/infobarproxy.h"
#include <QApplication>

#ifdef USE_KDE_BLUR
#include <KWindowEffects>
#endif

struct CurrentInfo {
    int index;
    int fileCount;
    QString fileName;
    QSize imageSize;
    qint64 fileSize;
};

enum ActiveSidePanel {
    SIDEPANEL_CROP,
    SIDEPANEL_NONE
};

class MW : public OverlayContainerWidget
{
    Q_OBJECT
public:
    explicit MW(QWidget *parent = nullptr);
    bool isCropPanelActive();
    void onScalingFinished(std::unique_ptr<QPixmap>scaled);
    void showImage(std::unique_ptr<QPixmap> pixmap);
    void showAnimation(std::unique_ptr<QMovie> movie);
    void showVideo(QString file);

    void setCurrentInfo(int fileIndex, int fileCount, QString fileName, QSize imageSize, qint64 fileSize);
    void setExifInfo(QMap<QString, QString>);
    std::shared_ptr<DirectoryViewWrapper> getFolderView();
    std::shared_ptr<DirectoryViewWrapper> getThumbnailPanel();

private:
    std::shared_ptr<ViewerWidget> viewerWidget;
    QHBoxLayout layout;
    QTimer windowMoveTimer;
    int currentDisplay;
    QDesktopWidget *desktopWidget;

    QColor bgColor;
    qreal bgOpacity;
    bool panelEnabled, panelFullscreenOnly, cropPanelActive, showInfoBarFullscreen, showInfoBarWindowed;
    std::shared_ptr<DocumentWidget> docWidget;
    std::shared_ptr<FolderViewProxy> folderView;
    std::shared_ptr<CentralWidget> centralWidget;
    ActiveSidePanel activeSidePanel;
    std::shared_ptr<ThumbnailStrip> thumbnailStrip;
    MainPanel *mainPanel;
    SidePanel *sidePanel;
    CropPanel *cropPanel;
    CropOverlay *cropOverlay;
    SaveConfirmOverlay *saveOverlay;
    ChangelogWindow *changelogWindow;

    CopyOverlay *copyOverlay;

    RenameOverlay *renameOverlay;

    ImageInfoOverlayProxyWrapper *imageInfoOverlay;

    ControlsOverlay *controlsOverlay;
    InfoOverlayProxyWrapper *infoBarFullscreen;
    std::shared_ptr<InfoBarProxy> infoBarWindowed;
    FloatingMessageProxy *floatingMessage;

    PanelHPosition panelPosition;
    QPoint lastMouseMovePos;
    CurrentInfo info;

    void saveWindowGeometry();
    void restoreWindowGeometry();
    void saveCurrentDisplay();
    void setupUi();

    void applyWindowedBackground();
    void applyFullscreenBackground();
    void mouseDoubleClickEvent(QMouseEvent *event);

    void setupCropPanel();
    void setupCopyOverlay();
    void setupSaveOverlay();
    void setupRenameOverlay();

private slots:
    void updateCurrentDisplay();
    void readSettings();
    void adaptToWindowState();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    bool event(QEvent *event);
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *event);
    void resizeEvent(QResizeEvent *event);
    void leaveEvent(QEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void opened(QString);
    void fullscreenStateChanged(bool);
    void copyRequested(QString);
    void moveRequested(QString);
    void resizeRequested(QSize);
    void renameRequested(QString);
    void cropRequested(QRect);
    void discardEditsRequested();
    void saveAsClicked();
    void saveRequested();
    void saveAsRequested(QString);
    void sortingSelected(SortingMode);

    // viewerWidget
    void scalingRequested(QSize, ScalingFilter);
    void zoomIn();
    void zoomOut();
    void zoomInCursor();
    void zoomOutCursor();
    void scrollUp();
    void scrollDown();
    void scrollLeft();
    void scrollRight();
    void pauseVideo();
    void stopPlayback();
    void seekVideoRight();
    void seekVideoLeft();
    void frameStep();
    void frameStepBack();
    void enableDocumentView();
    void setDirectoryPath(QString);
    void toggleTransparencyGrid();
    void droppedIn(const QMimeData*, QObject*);
    void draggedOut();

public slots:
    void setupFullUi();

    void showDefault();
    void showCropPanel();
    void hideCropPanel();
    void toggleFolderView();
    void enableFolderView();
    void showOpenDialog(QString path);
    void showSaveDialog(QString filePath);
    void showResizeDialog(QSize initialSize);
    void showSettings();
    void triggerFullScreen();
    void showMessageDirectoryEnd();
    void showMessageDirectoryStart();
    void showMessageFitWindow();
    void showMessageFitWidth();
    void showMessageFitOriginal();
    void showFullScreen();
    void showWindowed();
    void triggerCopyOverlay();
    void showMessage(QString text);
    void showMessage(QString text, int duration);
    void showMessageSuccess(QString text);
    void showWarning(QString text);
    void showError(QString text);
    void triggerMoveOverlay();
    void closeFullScreenOrExit();
    void close();
    void triggerCropPanel();
    void updateCropPanelData();
    void showSaveOverlay();
    void hideSaveOverlay();
    void showChangelogWindow();
    void showChangelogWindow(QString text);
    void fitWindow();
    void fitWidth();
    void fitOriginal();
    void switchFitMode();
    void closeImage();
    void showContextMenu();
    void onSortingChanged(SortingMode);
    void toggleImageInfoOverlay();
    void toggleRenameOverlay();
    void setFilterNearest();
    void setFilterBilinear();
    void toggleScalingFilter();
};

#endif // MainWindow_H
